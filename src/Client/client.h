#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../Client/SDL/gamescreen.h"
#include "../Common/Config/ClientConfig.h"
#include "../Common/DTO/game.h"
#include "../Common/Types/command.h"
#include "../Common/socket.h"
#include "./Protocol/deserializer.h"
#include "./Protocol/serializer.h"
#include "./Threads/receiverThread.h"
#include "./Threads/senderThread.h"
#include "Controllers/GameController.h"
#include "Controllers/LobbyController.h"
#include "Lobby/lobbyInit.h"

class Client {
private:
    char* ip;
    char* port;
    std::shared_ptr<Socket> skt;
    std::atomic<bool> was_closed;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> senderQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> lobbyQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> gameQueue;
    SenderThread sender;
    Serializer serializer;
    Deserializer deserializer;
    ReceiverThread receiver;
    LobbyController lobbyController;
    GameController gameController;


public:
    Client(char* ip, char* port);
    void start();

};

#endif  // CLIENT_H
