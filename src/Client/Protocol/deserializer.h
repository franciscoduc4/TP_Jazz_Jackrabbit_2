#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../Common/DTO/dto.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/Types/command.h"


class Deserializer {
private:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue;

public:
    Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue);

    void deserialize_msg(Command cmd, std::vector<char>& buffer);

    void receiveSnapshot(std::vector<char>& buffer);
};

#endif
