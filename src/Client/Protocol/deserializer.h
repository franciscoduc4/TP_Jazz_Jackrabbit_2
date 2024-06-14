#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>

#include "../../Common/DTO/dto.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/DTO/gamesList.h"


class Deserializer {
private:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue;
    

public:
    Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue,
        std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue);

    void deserialize_lobbyMsg(std::unique_ptr<DTO>& dto);

    void deserialize_gameMsg(std::unique_ptr<DTO>& dto);

    void setPlayerId(uint32_t playerId);
};

#endif
