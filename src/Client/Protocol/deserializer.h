#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "../../Common/socket.h"
#include "../../Common/DTO/dto.h"
#include "../../Common/queue.h"

#include <map>
#include <vector>
#include <cstdint>
#include <memory>


class Deserializer {
private:
    std::shared_ptr<Queue<DTO>>& queue;
public:
    Deserializer(std::shared_ptr<Queue<DTO>>& queue);

	void deserialize_msg(DTO& dto);
};

#endif
