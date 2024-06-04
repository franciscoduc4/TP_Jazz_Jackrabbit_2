#include "../Common/socket.h"
#include "../Common/DTO/dto.h"

#include <map>
#include <vector>
#include <cstdint>


class Deserializer {
private:

public
	void deserialize_msg(DTO& dto);

    void lobby_msg(DTO& dto);

    void command_msg(DTO& dto);

    void show_snapshot(DTO& dto);
}
