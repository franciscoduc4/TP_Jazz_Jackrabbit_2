#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <map>
#include <string>
#include <utility>
#include <vector>
<<<<<<< HEAD:src/Common/protocol.h

#include "socket.h"

class GameStatus;  // Forward declaration
=======
#include <atomic>

#include "socket.h"

class GameStatus;
>>>>>>> client:Common/protocol.h

struct ProtocolMessage {
    std::uint8_t cmd;
    std::string args;
<<<<<<< HEAD:src/Common/protocol.h
=======
    
>>>>>>> client:Common/protocol.h

    ProtocolMessage() = default;
    ProtocolMessage(std::uint8_t cmd, std::string args): cmd(cmd), args(std::move(args)) {}
};

class Protocol {
    Socket socket;
<<<<<<< HEAD:src/Common/protocol.h

public:
    explicit Protocol(Socket&& socket);
=======
    std::atomic<bool> was_closed;

    void send_msg(void* data, size_t size);
    void recv_msg(void* data, size_t size);


public:
    explicit Protocol(Socket&& socket);

    bool server_closed();

>>>>>>> client:Common/protocol.h
    void sendMessage(const ProtocolMessage& message);
    ProtocolMessage recvMessage();
    void sendGameState(GameStatus& gameStatus);
    void sendJoinGame(const std::string& gameName);
    void sendCreateGame(const std::string& gameName);
    void sendSetName(const std::string& name);

    int getId() const;
};

#endif  // PROTOCOL_H_
