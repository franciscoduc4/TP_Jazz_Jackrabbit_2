#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <utility>
#include <map>
#include <vector>
#include "../Common/socket.h"

class Protocol {
    Socket socket;

public:
    explicit Protocol(Socket&& socket): socket(std::move(socket)) {}
    void sendMessage(const std::string& message);
    std::string recvMessage();
    void Protocol::sendGameState(GameStatus& gameStatus);

    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);
};

#endif  // SERVER_PROTOCOL_H_
