#include "../Common/socket.h"
#include "../Common/DTO/dto.h"

#include <map>
#include <vector>
#include <cstdint>


class Deserializer {
private:
    std::shared_ptr<Queue<DTO>>& queue;
public
    Deserializer(std::shared_ptr<Queue<DTO>>& queue);

	void deserialize_msg();
}
