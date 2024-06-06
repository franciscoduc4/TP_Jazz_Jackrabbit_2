#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../Common/DTO/game.h"
#include "../Common/Types/command.h"
#include "../Common/socket.h"
#include "./Protocol/deserializer.h"
#include "./Protocol/serializer.h"
// #include "./Threads/cmdReaderThread.h"
#include "./Threads/receiverThread.h"
#include "./Threads/senderThread.h"
#include "Lobby/lobbyInit.h"
#include "../Common/Types/command.h"

class Client {
private:
    char* ip;
    char* port;
    std::shared_ptr<Socket> skt;
    std::atomic<bool> was_closed;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> senderQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> playerCmdsQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> receiverQueue;
    SenderThread sender;
    Serializer serializer;
    // CmdReaderThread cmdReader;
    Deserializer deserializer;
    ReceiverThread receiver;
	int32_t playerId;

public:
    Client(char* ip, char* port);
    void start();
    std::unique_ptr<DTO> getServerMsg();
    void sendMsg(Command& cmd, std::vector<uint8_t>& parameters);
	void move_msg(std::vector<uint8_t>& parameters);
};

#endif  // CLIENT_H
