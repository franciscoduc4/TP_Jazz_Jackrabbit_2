#include "protocol.h"

Protocol::Protocol(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame)
    : socket(socket), keepPlaying(keepPlaying), inGame(inGame), wasClosed(false) {}

void Protocol::clientClosed() {
    this->keepPlaying.store(false);
    this->inGame.store(false);
}

void Protocol::sendData(const std::vector<char>& data) {
    socket->sendall(data.data(), data.size(), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

void Protocol::sendId(uint8_t id) {
    const auto* p = reinterpret_cast<const unsigned char*>(&id);
    socket->sendall(p, sizeof(uint8_t), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

void Protocol::sendDTOType(char dtoType) {
    socket->sendall(&dtoType, sizeof(char), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

void Protocol::setInGame(bool inGameStatus) {
    this->inGame.store(inGameStatus);
}

bool Protocol::receiveUInt8(uint8_t& value) {
    socket->recvall(&value, sizeof(uint8_t), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}

bool Protocol::receiveChar(char& value) {
    socket->recvall(&value, sizeof(char), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}

bool Protocol::receiveVectorChar(std::vector<char>& buffer) {
    socket->recvall(buffer.data(), buffer.size(), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}
