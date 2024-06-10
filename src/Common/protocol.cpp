#include "protocol.h"

#include <sstream>
#include <stdexcept>
#include <utility>

#include <arpa/inet.h>

#include "socket.h"
// #include "../Server/Game/gameStatus.h"

Protocol::Protocol(Socket&& socket): socket(std::move(socket)), was_closed(false) {}

bool Protocol::server_closed() {
    return this->was_closed;
}

void Protocol::send_msg(void* data, size_t size) {
    socket.sendall(data, size, &this->was_closed);
}

void Protocol::sendMessage(const ProtocolMessage& message) {

    std::uint8_t cmd = message.cmd;
    std::string args = message.args;

    std::string payload = std::to_string(cmd) + " " + args;
    uint16_t payloadSize = htonl(payload.size());

     // Envío la longitud del mensaje
    this->send_msg(&payloadSize, sizeof(uint16_t));

    // Envío el payload del mensaje
    this->send_msg(&payload, payload.size());
}

void Protocol::recv_msg(void* data, size_t size) {
    socket.recvall(data, size, &this->was_closed);
    if (was_closed) {
        throw std::runtime_error("Socket closed");
    }
}

ProtocolMessage Protocol::recvMessage() {
    uint16_t payloadSize;

    // Recibo la longitud del mensaje
    this->recv_msg(&payloadSize, sizeof(uint16_t));

    payloadSize = ntohl(payloadSize);
    std::string message(payloadSize, '\0');

    // Recibo el comando
    this->recv_msg(&message[0], payloadSize);

    ProtocolMessage protocolMessage;
    std::istringstream iss(message);
    iss >> protocolMessage.cmd;
    std::getline(iss, protocolMessage.args);

    return protocolMessage;
}

// void Protocol::sendGameState(GameStatus& gameStatus) {
//     ProtocolMessage currentGameStatus;
//     currentGameStatus.cmd = 0x00;
//     currentGameStatus.args = gameStatus.snapshot();
//     sendMessage(currentGameStatus);
// }

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


// int Protocol::getId() const { return socket.getSocketId(); }
