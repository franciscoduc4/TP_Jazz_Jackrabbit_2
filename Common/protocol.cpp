#include "protocol.h"

Protocol::Protocol(Socket&& socket): socket(std::move(socket)) {}

void Protocol::sendMessage(const std::string& message) { socket.send(message); }