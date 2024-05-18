#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>

#include "../Common/socket.h"

class Protocol {
    Socket socket;

public:
    Protocol(Socket&& socket): socket(std::move(socket)) {}
    void sendMessage(const std::string& message);
    std::string recvMessage();
};

#endif  // SERVER_PROTOCOL_H_