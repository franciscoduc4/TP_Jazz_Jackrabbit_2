#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "../../Common/DTO/dto.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/DTO/gamesList.h"


class Deserializer {
private:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue;

public:
    Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue);

    void deserialize_msg(std::unique_ptr<DTO>& dto);

    std::map<int32_t, std::vector<GameInfo>> getGamesList(std::unique_ptr<DTO>& dto);
};

#endif
