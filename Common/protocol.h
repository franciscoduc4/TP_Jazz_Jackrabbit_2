#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "../Common/socket.h"

#include "gameStatus.h"

struct ProtocolMessage {
    std::uint8_t cmd;
    std::string args;

    ProtocolMessage() = default;
    ProtocolMessage(std::uint8_t cmd, std::string args): cmd(cmd), args(std::move(args)) {}
};

class Protocol {
    Socket socket;

public:
    explicit Protocol(Socket&& socket);
    explicit Protocol(Socket& socket);
    void sendMessage(const ProtocolMessage& message);
    ProtocolMessage recvMessage();
    void sendGamesList(GameMonitor& gameMonitor);
    void sendGameState(GameStatus& gameStatus);
    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);
};

#endif  // SERVER_PROTOCOL_H_
