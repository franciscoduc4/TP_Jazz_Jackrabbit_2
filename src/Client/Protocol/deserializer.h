#include "../Common/socket.h"

#include <map>
#include <vector>
#include <cstdint>


class Deserializer {
private:
	std::shared_ptr<Socket> skt;

	std::unique_ptr<GameDTO> show_snapshot(bool& was_closed)
	
	
public:
	explicit Deserializer(std::shared_ptr<Socket> socket);

	std::unique_ptr<CommandDTO> deserializar_msg();
	
	
}
