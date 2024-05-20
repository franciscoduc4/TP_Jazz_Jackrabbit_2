#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "../Server/Game/gameStatus.h"

#include "socket.h"

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
    void sendMessage(const ProtocolMessage& message);
    ProtocolMessage recvMessage();
    void sendGameState(GameStatus& gameStatus);
    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);

    int getId() const;
};

#endif  // PROTOCOL_H_