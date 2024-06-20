#ifndef LOBBYCONTROLLER_H
#define LOBBYCONTROLLER_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"
#include "DTO/createGame.h"
#include "DTO/gameUpdate.h"
#include "DTO/mapsList.h"
#include "DTO/startGame.h"

class LobbyController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::unordered_map<uint8_t, GameInfo> games;
    GameInfo selected;

public:
    LobbyController(Serializer& serializer, Deserializer& deserializer,
                    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue);
    // UPDATES
    bool hasGameUpdates(std::unique_ptr<DTO>& dto);
    int processGameUpdate(std::unique_ptr<CommandDTO>& dto);
    bool canStartGame();
    GameInfo getSelectedGame();

    // OUTBOUND METHODS
    void sendRequest(const LobbyMessage& msg);
    void startGame(const LobbyMessage& msg);

    // INBOUND METHODS
    std::pair<bool, GameInfo> recvResponse();
    bool recvStartGame();
    uint8_t recvCreateGame();
    std::unordered_map<uint8_t, std::string> getMaps();
    std::unordered_map<uint8_t, GameInfo>& getGamesList();
};

#endif  // LOBBYCONTROLLER_H
