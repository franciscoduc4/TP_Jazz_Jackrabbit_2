#include "protocol.h"

#include <sstream>
#include <stdexcept>
#include <utility>
<<<<<<< HEAD:src/Common/protocol.cpp
#include <arpa/inet.h>

//#include "..Server/gameStatus.h"
#include "Constants/lobbyCommands.h"
#include "Constants/playerCommands.h"

Protocol::Protocol(Socket&& socket): socket(std::move(socket)) {}

void Protocol::sendMessage(const ProtocolMessage& message) {
=======

#include <arpa/inet.h>

#include "../Common/socket.h"
#include "../Server/Game/gameStatus.h"
#include "Constants/lobbyCommands.h"
#include "Constants/playerCommands.h"

Protocol::Protocol(Socket&& socket): socket(std::move(socket)), was_closed(false) {}

bool Protocol::server_closed() {
    return this->was_closed.load();
}

void Protocol::send_msg(void* data, size_t size) {
    socket.sendall(data, size, &this->was_closed);
}

void Protocol::sendMessage(const ProtocolMessage& message) {

>>>>>>> client:Common/protocol.cpp
    std::uint8_t cmd = message.cmd;
    std::string args = message.args;

    std::string payload = std::to_string(cmd) + " " + args;
    uint16_t payloadSize = htonl(payload.size());
<<<<<<< HEAD:src/Common/protocol.cpp
    bool wasClosed = false;

    try {
        // Envio longitud del payload
        socket.sendall(&payloadSize, sizeof(uint16_t), &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
        // Envio el comando
        socket.sendall(payload.data(), payload.size(), &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
    } catch (const std::exception& e) {
        wasClosed = true;
=======

     // Envío la longitud del mensaje
    this->send_msg(&payloadSize, sizeof(uint16_t));

    // Envío el payload del mensaje
    this->send_msg(&payload, payload.size());
}

void Protocol::recv_msg(void* data, size_t size) {
    socket.recvall(data, size, &this->was_closed);
    if (was_closed) {
        throw std::runtime_error("Socket closed");
>>>>>>> client:Common/protocol.cpp
    }
}

ProtocolMessage Protocol::recvMessage() {
    uint16_t payloadSize;
<<<<<<< HEAD:src/Common/protocol.cpp
    bool wasClosed = false;

    try {
        // Recibo longitud
        socket.recvall(&payloadSize, sizeof(uint16_t), &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
    } catch (const std::exception& e) {
        wasClosed = true;
    }
=======

    // Recibo la longitud del mensaje
    this->recv_msg(&payloadSize, sizeof(uint16_t));
>>>>>>> client:Common/protocol.cpp

    payloadSize = ntohl(payloadSize);
    std::string message(payloadSize, '\0');

<<<<<<< HEAD:src/Common/protocol.cpp
    try {
        // Recibo el comando
        socket.recvall(&message[0], payloadSize, &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
    } catch (const std::exception& e) {
        wasClosed = true;
    }
=======
    // Recibo el comando
    this->recv_msg(&message[0], payloadSize);
>>>>>>> client:Common/protocol.cpp

    ProtocolMessage protocolMessage;
    std::istringstream iss(message);
    iss >> protocolMessage.cmd;
    std::getline(iss, protocolMessage.args);

    return protocolMessage;
}

void Protocol::sendGameState(GameStatus& gameStatus) {
    ProtocolMessage currentGameStatus;
    currentGameStatus.cmd = 0x00;
<<<<<<< HEAD:src/Common/protocol.cpp
    //currentGameStatus.args = gameStatus.snapshot();
=======
    currentGameStatus.args = gameStatus.snapshot();
>>>>>>> client:Common/protocol.cpp
    sendMessage(currentGameStatus);
}

// void Protocol::sendJoinGame(const std::string& gameName) {
//     std::ostringstream oss;
//     oss << JOIN_GAME << " " << gameName;
//     sendMessage(oss.str());
// }

// void Protocol::sendCreateGame(const std::string& gameName) {
//     std::ostringstream oss;
//     oss << CREATE_GAME << " " << gameName;
//     sendMessage(oss.str());
// }

<<<<<<< HEAD:src/Common/protocol.cpp
=======

>>>>>>> client:Common/protocol.cpp
int Protocol::getId() const { return socket.getSocketId(); }
