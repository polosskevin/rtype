//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#include "GameManager.h"

rtype::GameManager::GameManager(std::unique_ptr<rtype::GameLauncher> gl): launcher_(std::move(gl)) {}

int rtype::GameManager::createGame(rtype::protocol_tcp::CreateGame const &cg, std::shared_ptr<Connection> cptr) {
    static int uid = 1;
    auto gl = std::make_shared<GameLobby>(*this, cg, cptr, uid);
    lobbies_.push_back(gl);
    auto retId = uid;
    uid += 1;
    if (uid < 1) {
        uid = 1;
    }
    return retId;
}

rtype::GameManager::JoinGameResult rtype::GameManager::joinGame(rtype::protocol_tcp::JoinGameInfo const &jgi, std::shared_ptr<Connection> cptr) {
    auto uid = jgi.gameId;
    auto iOpt = std::find_if(lobbies_.begin(), lobbies_.end(), [uid](auto const & l){ return l->getId() == uid; });
    if (iOpt != lobbies_.end()) {
        (*iOpt)->joinGame(jgi, cptr);
        if ((*iOpt)->isFull()) {
            if (launcher_) {
                auto success = launcher_->launch(*iOpt);
            }
            lobbies_.erase(iOpt);
            return rtype::GameManager::JoinGameResult::STARTED;
        }
        return rtype::GameManager::JoinGameResult::JOINED;
    }
    return rtype::GameManager::JoinGameResult::FAILURE;
}

bool rtype::GameManager::leaveGame(int uid, std::shared_ptr<Connection> cptr) {
    auto iOpt = std::find_if(lobbies_.begin(), lobbies_.end(), [uid](auto const & l){ return l->getId() == uid; });
    if (iOpt != lobbies_.end()) {
        (*iOpt)->leaveGame(cptr);
        if ((*iOpt)->isEmpty()) {
            lobbies_.erase(iOpt);
        }
        return true;
    }
    return false;
}

std::vector<rtype::protocol_tcp::GameInfo> rtype::GameManager::getAllGameInfo() const {
    std::vector<rtype::protocol_tcp::GameInfo> ret;
    for (auto const & gl: lobbies_) {
        ret.push_back(gl->getGameInfo());
    }
    return ret;
}

std::shared_ptr<rtype::GameLobby> rtype::GameManager::getGameById(int uid) {
    auto iOpt = std::find_if(lobbies_.begin(), lobbies_.end(), [uid](auto const & l) { return l->getId() == uid; });
    return iOpt == lobbies_.end() ? nullptr : *iOpt;
}
