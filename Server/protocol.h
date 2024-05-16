#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>

class Protocol {
public:
    Protocol();
    void send(const std::string& message);
    std::string receive();
};

#endif  // SERVER_PROTOCOL_H_