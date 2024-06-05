#include "deserializer.h"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "../Common/DTO/dto.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/queue.h"

Deserializer::Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Deserializer::deserialize_msg(std::unique_ptr<DTO>& dto) { queue->push(std::move(dto)); }
