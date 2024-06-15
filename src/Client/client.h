#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>
#include <vector>

// #include "../Client/SDL/gamescreen.h"
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
#include "../Common/Types/command.h"

class Client {
private:
    char* ip;
    char* port;
    std::shared_ptr<Socket> skt;
    std::atomic<bool> was_closed;
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> senderQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> lobbyQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> gameQueue;
    SenderThread sender;
    Serializer serializer;
    Deserializer deserializer;
    ReceiverThread receiver;
    LobbyController lobbyController;
    GameController gameController;
    uint32_t playerId;

public:
    Client(char* ip, char* port);
    void start();
    std::unique_ptr<DTO> getServerMsg();
    void sendMsg(Command& cmd, std::vector<uint8_t>& parameters);
	void move_msg(std::vector<uint8_t>& parameters);
	void shoot_msg();
};

#endif  // CLIENT_H
