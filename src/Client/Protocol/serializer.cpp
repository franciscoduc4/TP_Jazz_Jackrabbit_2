#include "serializer.h"
#include "../Common/Types/command.h"
#include "../Common/Types/move.h"

#include <vector>
#include <cstdint>

Serialize::Serializer(std::shared_ptr<Queue<DTO>>& queue): queue(queue) {}

void Serializer::msg_create_game(int32_t& playerId, uint8_t& episode, uint8_t& gameMode, int& maxPlayers, uint8_t& character, std::vector<char>& name) {

    CreateGameDTO createGame(playerId, episode, gameMode, maxPlayers, character, name);
    queue.push(createGame);
}


void Serializer::msg_move(int32_t& playerId, uint8_t& mov_type) {
	MoveDTO move(playerId, mov_type);
    queue.push(move);
}
	
void Serializer::msg_shoot(int32_t& playerId) {
    CommandDTO shoot(playerId, Command::SHOOT);
    queue.push(shoot);

}

void Serialize::msg_jump(int32_t& playerId) {
	CommandDTO jump(playerId, Command::JUMP);
    queue.push(jump);
}


void Serialize::msg_run(int32_t& playerId) {
	CommandDTO run(playerId, Command::RUN);
    queue.push(run);
}

void Serialize::msg_dash(int32_t& playerId) {
    CommandDTO dash(playerId, Command::DASH);
    queue.push(dash);
}




