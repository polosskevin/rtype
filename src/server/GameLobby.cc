//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include <algorithm>
#include <Resolver.h>
#include "GameLobby.h"

rtype::GameLobby::GameLobby(
        GameManager &gm,
        rtype::protocol_tcp::CreateGame const &cg,
        int uid):
        gm_(gm) {
    gi_.gameId = uid;
    gi_.nbPlayerMax = cg.nbPlayerMax;
    gi_.filename = cg.fileName;
}

void rtype::GameLobby::joinGame(rtype::protocol_tcp::JoinGameInfo const &jgi, std::shared_ptr<Connection> cptr) {
    cs_.push_back(cptr);
//    auto host = cptr->
//    endPoints_.push_back();
    endPoints_.push_back(std::make_pair(cptr->getRemoteIp(), jgi.port));
    gi_.playersNames.push_back(jgi.playerName);
}

void rtype::GameLobby::leaveGame(std::shared_ptr<Connection> cptr) {
    auto it = std::find(cs_.begin(), cs_.end(), cptr);
    if (it != cs_.end()) {
        auto i = it - cs_.begin();
        cs_.erase(it);
        gi_.playersNames.erase(gi_.playersNames.begin() + i);
    }
}

bool rtype::GameLobby::isFull() {
    return gi_.nbPlayerMax == cs_.size();
}

bool rtype::GameLobby::isEmpty() {
    return cs_.empty();
}

int rtype::GameLobby::getId() const {
    return gi_.gameId;
}

rtype::protocol_tcp::GameInfo const &rtype::GameLobby::getGameInfo() const {
    return gi_;
}

std::vector<std::pair<std::string, std::string>> const & rtype::GameLobby::getIpAndPorts() const {
    return endPoints_;
}

void rtype::GameLobby::notifyAllGameStart(rtype::protocol_tcp::GameStart &gs) const {
    int i = 1;
    for (auto c: cs_) {
        gs.value.id = i++;
        auto s = rtype::protocol_tcp::transform(gs);
        c->sendString(s);
    }
}
