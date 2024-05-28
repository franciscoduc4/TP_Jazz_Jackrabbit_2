#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <atomic>

#include "socket.h"

class GameStatus;

struct ProtocolMessage {
    std::uint8_t cmd;
    std::string args;
    

    ProtocolMessage() = default;
    ProtocolMessage(std::uint8_t cmd, std::string args): cmd(cmd), args(std::move(args)) {}
};

class Protocol {
    Socket socket;
    std::atomic<bool> was_closed;

    void send_msg(void* data, size_t size);
    void recv_msg(void* data, size_t size);


public:
    explicit Protocol(Socket&& socket);

    bool server_closed();

    void sendMessage(const ProtocolMessage& message);
    ProtocolMessage recvMessage();
    void sendGameState(GameStatus& gameStatus);
    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);

    int getId() const;
};

#endif  // PROTOCOL_H_
