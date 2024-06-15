#ifndef CLIENT_SERIALIZER_H
#define CLIENT_SERIALIZER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../Common/DTO/dto.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "DTO/command.h"
#include "Types/lobbyMessage.h"

class Serializer {
private:
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue;

public:
    explicit Serializer(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue);

    void sendMsg(std::unique_ptr<CommandDTO>& dto);

    void serializeLobbyMessage(const LobbyMessage& msg);
};

#endif  // CLIENT_SERIALIZER_H
