#include "../Common/socket.h"

#include <vector>
#include <cstdint>

class Serializer {
private:
    std::shared_ptr<Queue<DTO>>& queue;

public:
	explicit Serializer(std::shared_ptr<Queue<DTO>>& queue);
	
	void msg_create_game(uint8_t& episode, uint8_t& gameMode, uint8_t& maxPlayers, uint8_t& character, std::vector<char>& name);

	void msg_move(uint8_t& mov_type);
	
	void msg_shoot();
	
	void msg_jump();

	void msg_run();

	void msg_dash();


}
