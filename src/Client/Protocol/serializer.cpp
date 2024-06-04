#include "serializer.h"
#include "../Common/Types/command.h"
#include "../Common/Types/move.h"

#include <vector>
#include <cstdint>

Serialize::Serializer(std::shared_ptr<Queue<DTO>>& queue): queue(queue) {}

void Serializer::sendMsg(DTO& dto) { queue.push(dto); }



