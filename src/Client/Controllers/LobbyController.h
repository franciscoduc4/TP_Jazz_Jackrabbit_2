#ifndef LOBBYCONTROLLER_H
#define LOBBYCONTROLLER_H

#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>

#include "DTO/createGame.h"
#include "DTO/mapsList.h"
#include "DTO/startGame.h"

class LobbyController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::unordered_map<uint32_t, GameInfo> games;
    GameInfo selected;

public:
    LobbyController(Serializer& serializer, 
        Deserializer& deserializer, 
        std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue);
    void sendRequest(const LobbyMessage& msg);
    bool recvResponse();
    void startGame(const LobbyMessage& msg);
    bool recvStartGame();
    std::unordered_map<uint32_t, std::string> getMaps();
    std::unordered_map<uint32_t, GameInfo>& getGamesList();

};

#endif  // LOBBYCONTROLLER_H
