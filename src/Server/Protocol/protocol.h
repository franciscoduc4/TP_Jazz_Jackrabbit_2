#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <memory>
#include <vector>
#include <atomic>
#include "../../Common/socket.h"

class Protocol {
private:
    std::shared_ptr<Socket> socket;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    bool wasClosed;

    void clientClosed();

public:
    Protocol(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
             std::atomic<bool>& inGame);

    void sendData(const std::vector<char>& data);
    void sendId(uint8_t id);
    void sendDTOType(char dtoType);
    void setInGame(bool inGameStatus);

    bool receiveUInt8(uint8_t& value);
    bool receiveChar(char& value);
    bool receiveVectorChar(std::vector<char>& buffer);

};


#endif  // SERVER_PROTOCOL_H
