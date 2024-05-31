#include "deserializer.h"
#include "../Common/command.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"

#include <vector>
#include <map>
#include <cstdint>

enum index_pos { PLAYER, ENEMY, GEMS, GOLDCOIN, SILVERCOIN }

Deserializer::Deserializer(std::shared_ptr<Socket> socket): skt(socket) {}

std::map<int, std::vector<uint8_t>> Deserializer::deserializar_msg() {
	
	bool was_closed;
	uint8_t command;
	skt->recvall(&command, sizeof(uint8_t), &was_closed);
	
	switch (command) {
		case GAME_STATUS:
			return show_snapshot(was_closed);			
	}	
}


std::map<uint8_t, std::vector<uint8_t>> Deserializer::show_snapshot(was_closed) {
	std::map<int, std::vector<uint8_t>> map_pos;

	std::vector<uint8_t> player_pos;
	uint8_t player
	skt->recvall(&player, sizeof(uint8_t), &was_closed);
	uint8_t pos_x;
	skt->recvall(&pos_x, sizeof(uint8_t), &was_closed);
	player.push_back(pos_x);
	uint8_t pos_y; 
	skt->recvall(&pos_y, sizeof(uint8_t), &was_closed);
	player.push_back(pos_y);
	map_pos[PLAYER] = player;
	
	//REPETIR ESTE PROCEDIMIENTO PARA TODOS LOS ENEMIGOS QUE SE IMPLEMENTEN
	uint8_t cant_enemies;
	skt->recvall(&cant_enemies, sizeof(uint8_t), &was_closed);
	uint8_t pos_x_enemy;
	uint8_t pos_y_enemy;
	map_pos[ENEMY] = std::vector<uint8_t> pos_enemy;
	for (int i = 0; i < cant_enemies; i++) {
		skt->recvall(&pos_x_enemy, sizeof(uint8_t), &was_closed);
		map_pos[ENEMY].push_back(pos_x_enemy);
		skt->recvall(&pos_y_enemy, sizeof(uint8_t), &was_closed);
		map_pos[ENEMY].push_back(pos_y_enemy);	
	}
	
	
	uint8_t cant_gems;
	skt->recvall(&cant_gems, sizeof(uint8_t), &was_closed);
	uint8_t pos_x_gems;
	uint8_t pos_y_gems;
	map_pos[GEMS] = std::vector<uint8_t> pos_gems;
	for (int i = 0; i < cant_gems; i++) {
		skt->recvall(&pos_x_gems, sizeof(uint8_t), &was_closed);
		map_pos[GEMS].push_back(pos_x_gems);
		skt->recvall(&pos_y_gems, sizeof(uint8_t), &was_closed);
		map_pos[GEMS].push_back(pos_y_gems);	
	}

	uint8_t cant_goldcoin;
	skt->recvall(&cant_goldcoin, sizeof(uint8_t), &was_closed);
	uint8_t pos_x_goldcoin;
	uint8_t pos_y_goldcoin;
	map_pos[GOLDCOIN] = std::vector<uint8_t> pos_goldcoin;
	for (int i = 0; i < cant_goldcoin; i++) {
		skt->recvall(&pos_x_goldcoin, sizeof(uint8_t), &was_closed);
		map_pos[GOLDCOIN].push_back(pos_x_goldcoin);
		skt->recvall(&pos_y_goldcoin, sizeof(uint8_t), &was_closed);
		map_pos[GOLDCOIN].push_back(pos_y_goldcoin);	
	}
	
	uint8_t cant_silvercoin;
	skt->recvall(&cant_silvercoin, sizeof(uint8_t), &was_closed);
	uint8_t pos_x_silvercoin;
	uint8_t pos_y_silvercoin;
	map_pos[SILVERCOIN] = std::vector<uint8_t> pos_silvercoin;
	for (int i = 0; i < cant_silvercoin; i++) {
		skt->recvall(&pos_x_silvercoin, sizeof(uint8_t), &was_closed);
		map_pos[SILVERCOIN].push_back(pos_x_silvercoin);
		skt->recvall(&pos_y_silvercoin, sizeof(uint8_t), &was_closed);
		map_pos[SILVERCOIN].push_back(pos_y_silvercoin);	
	}
	
	return map_pos;
}

