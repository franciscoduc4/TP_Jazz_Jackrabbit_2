#include "protocol.h"

#include <sstream>
#include <stdexcept>
#include <utility>

#include <arpa/inet.h>

#include "../Common/socket.h"
#include "../Server/Game/gameStatus.h"
#include "Constants/lobbyCommands.h"
#include "Constants/playerCommands.h"

Protocol::Protocol(Socket& socket): socket(socket) {}
Protocol::Protocol(Socket&& socket): socket(std::move(socket)) {}


void Protocol::sendMessage(const ProtocolMessage& message) {

    std::uint8_t cmd = message.cmd;
    std::string args = message.args;

    std::string payload = std::to_string(cmd) + " " + args;
    uint16_t payloadSize = htonl(payload.size());
    bool wasClosed = false;

    try {
        // Envio longitud del payload
        socket.sendall(&payloadSize, sizeof(uint16_t), &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
        // Envio el comando
        socket.sendall(&payload, payloadSize, &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }

    } catch (const std::exception& e) {
        wasClosed = true;
    }
}

ProtocolMessage Protocol::recvMessage() {
    uint16_t payloadSize;
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

    payloadSize = ntohl(payloadSize);
    std::string message(payloadSize, '\0');

    try {
        // Recibo el comando
        socket.recvall(&message[0], payloadSize, &wasClosed);
        if (wasClosed) {
            throw std::runtime_error("Socket closed");
        }
    } catch (const std::exception& e) {
        wasClosed = true;
    }

    ProtocolMessage protocolMessage;
    std::istringstream iss(message);
    iss >> protocolMessage.cmd;
    std::getline(iss, protocolMessage.args);

    return protocolMessage;
}

void Protocol::sendGamesList(GameMonitor& gameMonitor) {
    ProtocolMessage gamesList;
    gamesList.cmd = 0x04;
    gamesList.args = gameMonitor.listGames();
    sendMessage(gamesList);
}

void Protocol::sendGameState(GameStatus& gameStatus) {
    ProtocolMessage currentGameStatus;
    currentGameStatus.cmd = 0x00;
    currentGameStatus.args = gameStatus.snapshot();
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
