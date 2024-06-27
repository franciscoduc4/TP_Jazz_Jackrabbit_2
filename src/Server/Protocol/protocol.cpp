#include "protocol.h"

/*
 * Constructor de Protocol.
 * Inicializa el protocolo con el socket, keepPlaying, inGame y el estado de cerrado.
 */
Protocol::Protocol(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame)
    : socket(socket), keepPlaying(keepPlaying), inGame(inGame), wasClosed(false) {}

/*
 * Maneja el cierre del cliente, actualizando los indicadores de keepPlaying y inGame.
 */
void Protocol::clientClosed() {
    this->keepPlaying.store(false);
    this->inGame.store(false);
}

/*
 * Envía datos a través del socket.
 * Si el socket se cierra durante el envío, se llama a clientClosed.
 */
void Protocol::sendData(const std::vector<char>& data) {
    socket->sendall(data.data(), data.size(), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

/*
 * Envía el ID del jugador a través del socket.
 * Si el socket se cierra durante el envío, se llama a clientClosed.
 */
void Protocol::sendId(uint8_t id) {
    const auto* p = reinterpret_cast<const unsigned char*>(&id);
    socket->sendall(p, sizeof(uint8_t), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

/*
 * Envía el tipo de DTO a través del socket.
 * Si el socket se cierra durante el envío, se llama a clientClosed.
 */
void Protocol::sendDTOType(char dtoType) {
    socket->sendall(&dtoType, sizeof(char), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
    }
}

/*
 * Establece el estado de inGame.
 */
void Protocol::setInGame(bool inGameStatus) {
    this->inGame.store(inGameStatus);
}

/*
 * Recibe un valor uint8_t del socket.
 * Si el socket se cierra durante la recepción, se llama a clientClosed.
 * Devuelve true si la recepción fue exitosa, false si el socket fue cerrado.
 */
bool Protocol::receiveUInt8(uint8_t& value) {
    socket->recvall(&value, sizeof(uint8_t), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}

/*
 * Recibe un valor char del socket.
 * Si el socket se cierra durante la recepción, se llama a clientClosed.
 * Devuelve true si la recepción fue exitosa, false si el socket fue cerrado.
 */
bool Protocol::receiveChar(char& value) {
    socket->recvall(&value, sizeof(char), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}

/*
 * Recibe un vector de chars del socket.
 * Si el socket se cierra durante la recepción, se llama a clientClosed.
 * Devuelve true si la recepción fue exitosa, false si el socket fue cerrado.
 */
bool Protocol::receiveVectorChar(std::vector<char>& buffer) {
    socket->recvall(buffer.data(), buffer.size(), &wasClosed);
    keepPlaying.store(!wasClosed);
    if (wasClosed) {
        clientClosed();
    }
    return !wasClosed;
}
