#include "deserializer.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/DTO/dto.h"
#include "../Common/queue.h"


#include <vector>
#include <map>
#include <cstdint>
#include <memory>
Deserializer::Deserializer(std::shared_ptr<Queue<DTO>>& queue): queue(queue) {}

void Deserializer::deserialize_msg(DTO& dto) {
    queue->push(dto);
}

