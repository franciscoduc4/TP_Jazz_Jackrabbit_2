#ifndef SERIALIZER_CLIENT_H
#define SERIALIZER_CLIENT_H
#include "../../Common/socket.h"
#include "../../Common/queue.h"
#include "../../Common/DTO/dto.h"

#include <vector>
#include <cstdint>
#include <memory>

class Serializer {
private:
    std::shared_ptr<Queue<DTO>>& queue;

public:
	explicit Serializer(std::shared_ptr<Queue<DTO>>& queue);
	
	void sendMsg(DTO& dto);

};

#endif  // SERIALIZER_CLIENT_H
