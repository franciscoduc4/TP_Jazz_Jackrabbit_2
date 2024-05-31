#include "serializer.h"
#include "../Common/Types/command.h"
#include "../Common/Types/move.h"

#include <vector>
#include <cstdint>


bool Serializer::msg_create_game(uint8_t& episode, uint8_t& gameMode, uint8_t& maxPlayers, uint8_t& character, uint8_t& lengthName, std::vector<char>& name) {
	bool was_closed = false;
	uint8_t createGame = CREATE_GAME;
	skt->sendall(&createGame, sizeof(uint8_t), &was_closed);
	skt->sendall(&episode, sizeof(uint8_t), &was_closed);
	skt->sendall(&gameMode, sizeof(uint8_t), &was_closed);
	skt->sendall(&maxPlayers, sizeof(uint8_t), &was_closed);
	skt->sendall(&character, sizeof(uint8_t), &was_closed);
	skt->sendall(&lengthName, sizeof(uint8_t), &was_closed);
	skt->sendall(&createGame, sizeof(char) * lengthName, &was_closed);
	
	return was_closed;

}


bool Serializer::msg_move(uint8_t& mov_type) {
	bool was_closed = false; 
	uint8_t move = MOVE;
	skt->sendall(&move, sizeof(uint8_t), &was_closed);
	
	skt->sendall(&mov_type, sizeof(uint8_t), &was_closed); 
	return was_closed;	
}
	
bool Serialize::msg_shoot() {
	bool was_closed = false; 
	uint8_t shoot = SHOOT;
	skt->sendall(&shoot, sizeof(uint8_t), &was_closed);
	
	return was_closed;	
}

bool Serialize::msg_jump() {
	bool was_closed = false; 
	uint8_t jump = JUMP;
	skt->sendall(&jump, sizeof(uint8_t), &was_closed);
	
	return was_closed;
}


bool Serialize::msg_run() {
	bool was_closed = false; 
	uint8_t run = RUN;
	skt->sendall(&run, sizeof(uint8_t), &was_closed);
	
	return was_closed;
}

bool Serialize::msg_dash() {
	bool was_closed = false; 
	uint8_t dash = DASH;
	skt->sendall(&dash, sizeof(uint8_t), &was_closed);
	
	return was_closed;
}




