//
// Created by Kévin POLOSSAT on 21/01/2018.
//

#ifndef RTYPE_GAMEMANAGER_H
#define RTYPE_GAMEMANAGER_H

#include "GameLobby.h"
#include "GameLauncher.h"

namespace rtype {
class GameManager {
public:
    GameManager(std::unique_ptr<GameLauncher> gl);
    GameManager(GameManager const & other) = delete;
    GameManager(GameManager && other) = delete;
    ~GameManager() = default;

    GameManager & operator = (GameManager const & other) = delete;
    GameManager & operator = (GameManager && other) = delete;

    int createGame(rtype::protocol_tcp::GameInfo const & gameInfo, std::shared_ptr<Connection> cptr);
    bool joinGame(int uid, std::shared_ptr<Connection> cptr);
    bool leaveGame(int uid, std::shared_ptr<Connection> cptr);
private:
    std::vector<std::shared_ptr<GameLobby>> lobbies_;
    std::unique_ptr<GameLauncher> launcher_;
};
}


#endif //RTYPE_GAMEMANAGER_H
