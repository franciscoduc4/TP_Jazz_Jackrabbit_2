#include "../Common/socket.h"

#include <map>
#include <vector>
#include <cstdint>


class Deserializer {
private:
	std::shared_ptr<Socket> skt;

	std::map<uint8_t, std::vector<uint8_t>> show_snapshot(bool& was_closed)
	
	
public:
	explicit Deserializer(std::shared_ptr<Socket> socket);

	std::vector<std::vector<uint8_t>> deserializar_msg();
	
	
}
