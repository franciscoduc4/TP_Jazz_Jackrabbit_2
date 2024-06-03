#include "deserializer.h"
#include "../Common/command.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"


#include <vector>
#include <map>
#include <cstdint>

Deserializer::Deserializer(std::shared_ptr<Socket> socket): skt(socket) {}

std::unique_ptr<CommandDTO> Deserializer::deserializar_msg() {
	
	bool was_closed;
	uint8_t command;
	skt->recvall(&command, sizeof(uint8_t), &was_closed);
	
	switch (command) {
		case GAME_STATUS:
			return show_snapshot(was_closed);			
	}	
}


std::unique_ptr<GameDTO> Deserializer::show_snapshot(was_closed) {
	std::vector<PlayerDTO> player;
		
	uint8_t pos_x;
	skt->recvall(&pos_x, sizeof(uint8_t), &was_closed);
	uint8_t pos_y; 
	skt->recvall(&pos_y, sizeof(uint8_t), &was_closed);
	uint8_t playerId;
	skt->recvall(&playerId, sizeof(uint8_t), &was_closed);
	uint8_t health;
	skt->recvall(&health, sizeof(uint8_t), &was_closed);
	uint8_t damage;
	skt->recvall(&damage, sizeof(uint8_t), &was_closed);
	uint8_t speed;
	skt->recvall(&speed, sizeof(uint8_t), &was_closed);
	
	player.push_back(std::make_unique<PlayerDTO>(pos_x, pos_y, playerId, health, damage, speed, /*sprite*/));
	
	
	std::vector<EnemyDTO> enemies;

	uint8_t cant_enemies;
	skt->recvall(&cant_enemies, sizeof(uint8_t), &was_closed);
	
	uint8_t pos_x_enemy;
	uint8_t pos_y_enemy; 
	uint8_t enemyId;
	uint8_t enemy_health;
	uint8_t enemy_damage;
	uint8_t enemy_speed;
	
	for (int i = 0; i < cant_enemies; i++) {
		skt->recvall(&pos_x_enemy, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_enemy, sizeof(uint8_t), &was_closed);
		skt->recvall(&enemyId, sizeof(uint8_t), &was_closed);
		skt->recvall(&enemy_health, sizeof(uint8_t), &was_closed);
		skt->recvall(&enemy_damage, sizeof(uint8_t), &was_closed);
		skt->recvall(&enemy_speed, sizeof(uint8_t), &was_closed);
		enemies.push_back(std::make_unique<EnemyDTO>(pos_x_enemy, pos_y_enemy, EnemyId, enemy_health, enemy_damage, enemy_speed, /*sprite*/)));
		
	}
	
	
	std::vector<ItemDTO> items;
	
	uint8_t cant_gems;
	skt->recvall(&cant_gems, sizeof(uint8_t), &was_closed);
	
	uint8_t pos_x_gems;
	uint8_t pos_y_gems;
	for (int i = 0; i < cant_gems; i++) {
		skt->recvall(&pos_x_gems, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_gems, sizeof(uint8_t), &was_closed);
		items.push_back(std::make_unique<ItemDTO>(pos_x_gems, pos_y_gems, /*sprite*/));	
	}

	uint8_t cant_goldcoin;
	skt->recvall(&cant_goldcoin, sizeof(uint8_t), &was_closed);

	uint8_t pos_x_goldcoin;
	uint8_t pos_y_goldcoin;

	for (int i = 0; i < cant_goldcoin; i++) {
		skt->recvall(&pos_x_goldcoin, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_goldcoin, sizeof(uint8_t), &was_closed);
		items.push_back(std::make_unique<ItemDTO>(pos_x_goldcoin, pos_y_goldcoin, /*sprite*/));	
	}
	
	uint8_t cant_silvercoin;
	skt->recvall(&cant_silvercoin, sizeof(uint8_t), &was_closed);
	
	uint8_t pos_x_silvercoin;
	uint8_t pos_y_silvercoin;
	
	for (int i = 0; i < cant_silvercoin; i++) {
		skt->recvall(&pos_x_goldcoin, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_goldcoin, sizeof(uint8_t), &was_closed);
		items.push_back(std::make_unique<ItemDTO>(pos_x_silvercoin, pos_y_silvercoin, /*sprite*/));
	}
		
	
	std::vector<BulletDTO> bullets;

	uint8_t cant_bullets;
	skt->recvall(&cant_bullets, sizeof(uint8_t), &was_closed);
	
	uint8_t pos_x_bullets;
	uint8_t pos_y_bullets;
	uint8_t bulletId;
	uint8_t bullet_damage;
	uint8_t speed;
	uint8_t shooterId;
	
	for (int i = 0; i < cant_bullets; i++) {
		skt->recvall(&pos_x_bullets, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_bullets, sizeof(uint8_t), &was_closed);
		skt->recvall(&bulletId, sizeof(uint8_t), &was_closed);
		skt->recvall(&bullet_damage, sizeof(uint8_t), &was_closed);
		skt->recvall(&speed, sizeof(uint8_t), &was_closed);
		skt->recvall(&shooterId, sizeof(uint8_t), &was_closed);
		bullets.push_back(std::make_unique<BulletDTO>(pos_x_bullets, pos_y_bullets, bulletId, bullet_damage, speed, /*sprite*/, shooterId));
	}


	//std::vector<WeaponDTO> weapons;
	
	
	std::vector<TileDTO> tiles;
	
	uint8_t cant_tiles;
	skt->recvall(&cant_tiles, sizeof(uint8_t), &was_closed);
	
	uint8_t pos_x_tiles;
	uint8_t pos_y_tiles;
		
	for (int i = 0; i < cant_tiles; i++) {
		skt->recvall(&pos_x_tiles, sizeof(uint8_t), &was_closed);
		skt->recvall(&pos_y_tiles, sizeof(uint8_t), &was_closed);
		
		tiles.push_back(std::make_unique<TileDTO>(pos_x_tiles, pos_y_tiles, /*sprite*/));
	}

		
	return std::make_unique<GameDTO>(player, enemies, bullets, items, weapons, tiles);
}

