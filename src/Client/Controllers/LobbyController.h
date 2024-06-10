#ifndef LOBBYCONTROLLER_H
#define LOBBYCONTROLLER_H


#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

class LobbyController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::map<int32_t, GameInfo> games;
    GameInfo selected;

public:
    LobbyController(Serializer& serializer, Deserializer& deserializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue);
    void sendRequest(const LobbyMessage& msg);
    void startGame(const LobbyMessage& msg);
    std::map<int32_t, GameInfo>& getGamesList();

};

#endif  // LOBBYCONTROLLER_H
