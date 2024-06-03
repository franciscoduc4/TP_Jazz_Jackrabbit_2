#include "../Common/socket.h"

#include <vector>
#include <cstdint>

class Serializer {
private:
	std::shared_ptr<Socket> skt;

public:
	explicit Serializer(std::shared_ptr<Socket> socket);
	
	bool msg_create_game(uint8_t& episode, uint8_t& gameMode, uint8_t& maxPlayers, uint8_t& character, uint8_t& lengthName, std::vector<char>& name);

	bool msg_move(uint8_t& mov_type);
	
	bool msg_shoot();
	
	bool msg_jump();

	bool msg_run();

	bool msg_dash();


}
