#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../Common/DTO/dto.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"


class Deserializer {
private:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue;


public:
    Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue,
                 std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue);

    void deserialize_lobbyMsg(std::unique_ptr<DTO>& dto);

    void deserialize_gameMsg(std::unique_ptr<DTO>& dto);

    std::map<uint8_t, std::vector<GameInfo>> getGamesList(std::unique_ptr<DTO>& dto);

    void deserialize_msg(Command cmd, std::vector<char>& buffer);

    void receiveSnapshot(std::vector<char>& buffer);

    void setPlayerId(uint8_t playerId);
};

#endif
