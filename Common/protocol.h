#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <utility>
#include <map>
#include <vector>
#include "../Common/socket.h"

struct ProtocolMessage {
    std::uint8_t cmd;
    std::string args;
};

class Protocol {
    Socket socket;

public:
    explicit Protocol(Socket&& socket);
    explicit Protocol(Socket& socket);
    void sendMessage(const ProtocolMessage& message);
    ProtocolMessage recvMessage();
    void sendGameState(GameStatus& gameStatus);
    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);
};

#endif  // SERVER_PROTOCOL_H_
