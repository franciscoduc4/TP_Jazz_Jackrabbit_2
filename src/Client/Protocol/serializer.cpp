#include "serializer.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "../Common/DTO/dto.h"
#include "../Common/Types/command.h"
#include "../Common/Types/direction.h"
#include "../Common/queue.h"

Serializer::Serializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Serializer::sendMsg(std::unique_ptr<DTO>& dto) { queue->push(std::move(dto)); }
