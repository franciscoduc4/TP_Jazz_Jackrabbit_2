#ifndef LOBBYCONTROLLER_H
#define LOBBYCONTROLLER_H


#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

#include <map>
#include <memory>
#include <utility>
class LobbyController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::map<uint32_t, GameInfo> games;
    GameInfo selected;

public:
    LobbyController(Serializer& serializer, 
        Deserializer& deserializer, 
        std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue);
    void sendRequest(const LobbyMessage& msg);
    bool recvResponse();
    void startGame(const LobbyMessage& msg);
    bool recvStartGame();
    std::map<uint32_t, GameInfo>& getGamesList();

};

#endif  // LOBBYCONTROLLER_H
