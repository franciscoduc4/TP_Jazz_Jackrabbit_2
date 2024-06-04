#include "serializer.h"
#include "../Common/Types/command.h"
#include "../Common/Types/move.h"
#include "../Common/queue.h"
#include "../Common/DTO/dto.h"

#include <vector>
#include <cstdint>
#include <memory>

Serializer::Serializer(std::shared_ptr<Queue<DTO>>& queue): queue(queue) {}

void Serializer::sendMsg(DTO& dto) { queue->push(dto); }



