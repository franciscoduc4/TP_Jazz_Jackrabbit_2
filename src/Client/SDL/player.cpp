#include "player.h"
#include "projectile.h"
#include "../../Common/sprite.h"
#include "../Common/Config/ClientConfig.h"


#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <SDL2pp/SDL2pp.hh>

#include <iostream>

Player::Player(int character) {
	this->width = ClientConfig::getPlayerWidth();
	this->height = ClientConfig::getPlayerHeight();
	this->flip = 0;
	this->init = false;
	
	this->image_path[CharacterType::JAZZ] = ClientConfig::getJazzFile();//"../assets/Characters/Jazz.png";
	
	std::vector<std::vector<int>> idle_sprites = ClientConfig::getJazzIdleSprites();
	for (int i = 0; i < idle_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::IDLE].push_back(RectangularSprite(idle_sprites[i]));
	}

	std::vector<std::vector<int>> walking_sprites = ClientConfig::getJazzWalkingSprites();
	for (int i = 0; i < walking_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::MOVING].push_back(RectangularSprite(walking_sprites[i]));
	}
				
	std::vector<std::vector<int>> running_sprites = ClientConfig::getJazzRunningSprites();
	for (int i = 0; i < running_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(running_sprites[i]));
	}
	
	std::vector<std::vector<int>> shooting_sprites = ClientConfig::getJazzShootingSprites();
	for (int i = 0; i < shooting_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(shooting_sprites[i]));
	}
	
	std::vector<std::vector<int>> jumping_sprites = ClientConfig::getJazzJumpingSprites();
	for (int i = 0; i < jumping_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(jumping_sprites[i]));
	}
	/*
	std::vector<std::vector<int>> dash_sprites = ClientConfig::getJazzDashingSprites();
	for (int i = 0; i < dash_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterEntityType::DASH].push_back(RectangularSprite(dash_sprites[i]));
	}
	*/
	std::vector<std::vector<int>> special_attack_sprites = ClientConfig::getJazzSpecialAttackSprites();
	for (int i = 0; i < special_attack_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(special_attack_sprites[i]));
	}
	
	std::vector<std::vector<int>> intoxicated_sprites = ClientConfig::getJazzIntoxicatedSprites();
	for (int i = 0; i < intoxicated_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(intoxicated_sprites[i]));
	}
	
	std::vector<std::vector<int>> taking_damage_sprites = ClientConfig::getJazzTakingDamageSprites();
	for (int i = 0; i < taking_damage_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(taking_damage_sprites[i]));
	}
	
	std::vector<std::vector<int>> dead_sprites = ClientConfig::getJazzDeadSprites();
	for (int i = 0; i < dead_sprites.size(); i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(dead_sprites[i]));
	}
	
	this->image_path[CharacterType::LORI] = ClientConfig::getLoriFile();//"../assets/Characters/Lori.png";

	std::vector<std::vector<int>> lori_idle_sprites = ClientConfig::getLoriIdleSprites();
	for (int i = 0; i < lori_idle_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::IDLE].push_back(RectangularSprite(lori_idle_sprites[i]));
	}

	std::vector<std::vector<int>> lori_walking_sprites = ClientConfig::getLoriWalkingSprites();
	for (int i = 0; i < lori_walking_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::MOVING].push_back(RectangularSprite(lori_walking_sprites[i]));
	}
				
	std::vector<std::vector<int>> lori_running_sprites = ClientConfig::getLoriRunningSprites();
	for (int i = 0; i < lori_running_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(lori_running_sprites[i]));
	}
	
	std::vector<std::vector<int>> lori_shooting_sprites = ClientConfig::getLoriShootingSprites();
	for (int i = 0; i < lori_shooting_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(lori_shooting_sprites[i]));
	}
	
	std::vector<std::vector<int>> lori_jumping_sprites = ClientConfig::getLoriJumpingSprites();
	for (int i = 0; i < lori_jumping_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(lori_jumping_sprites[i]));
	}
	/* 
	std::vector<std::vector<int>> lori_dashing_sprites = ClientConfig::getLoriDashingSprites();
	for (int i = 0; i < lori_dashing_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::DASH].push_back(RectangularSprite(lori_dashing_sprites[i]));
	}
	*/
	std::vector<std::vector<int>> lori_special_attack_sprites = ClientConfig::getLoriSpecialAttackSprites();
	for (int i = 0; i < lori_special_attack_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(lori_special_attack_sprites[i]));
	}
	
	std::vector<std::vector<int>> lori_intoxicated_sprites = ClientConfig::getLoriIntoxicatedSprites();
	for (int i = 0; i < lori_intoxicated_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(lori_intoxicated_sprites[i]));
	}

	std::vector<std::vector<int>> lori_taking_damage_sprites = ClientConfig::getLoriTakingDamageSprites();
	for (int i = 0; i < lori_taking_damage_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(lori_taking_damage_sprites[i]));
	}

	std::vector<std::vector<int>> lori_dead_sprites = ClientConfig::getLoriDeadSprites();
	for (int i = 0; i < lori_dead_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(lori_dead_sprites[i]));
	}
	
	
	this->image_path[CharacterType::SPAZ] = ClientConfig::getSpazFile();//"../assets/Characters/Spaz.png";

	std::vector<std::vector<int>> spaz_idle_sprites = ClientConfig::getSpazIdleSprites();
	for (int i = 0; i < spaz_idle_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::IDLE].push_back(RectangularSprite(spaz_idle_sprites[i]));
	}

	std::vector<std::vector<int>> spaz_walking_sprites = ClientConfig::getSpazWalkingSprites();
	for (int i = 0; i < spaz_walking_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::MOVING].push_back(RectangularSprite(spaz_walking_sprites[i]));
	}
				
	std::vector<std::vector<int>> spaz_running_sprites = ClientConfig::getSpazRunningSprites();
	for (int i = 0; i < spaz_running_sprites.size(); i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(spaz_running_sprites[i]));
	}
	
	std::vector<std::vector<int>> spaz_shooting_sprites = ClientConfig::getSpazShootingSprites();
	for (int i = 0; i < spaz_shooting_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(spaz_shooting_sprites[i]));
	}
	
	std::vector<std::vector<int>> spaz_jumping_sprites = ClientConfig::getSpazJumpingSprites();
	for (int i = 0; i < spaz_jumping_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(spaz_jumping_sprites[i]));
	}
	/* 
	std::vector<std::vector<int>> spaz_dashing_sprites = ClientConfig::getSpazDashingSprites();
	for (int i = 0; i < spaz_dashing_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::DASH].push_back(RectangularSprite(spaz_dashing_sprites[i]));
	}
	*/
	std::vector<std::vector<int>> spaz_special_attack_sprites = ClientConfig::getSpazSpecialAttackSprites();
	for (int i = 0; i < spaz_special_attack_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(spaz_special_attack_sprites[i]));
	}

	std::vector<std::vector<int>> spaz_intoxicated_sprites = ClientConfig::getSpazIntoxicatedSprites();
	for (int i = 0; i < spaz_intoxicated_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(spaz_intoxicated_sprites[i]));
	}

	std::vector<std::vector<int>> spaz_taking_damage_sprites = ClientConfig::getSpazTakingDamageSprites();
	for (int i = 0; i < spaz_taking_damage_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(spaz_taking_damage_sprites[i]));
	}

	std::vector<std::vector<int>> spaz_dead_sprites = ClientConfig::getSpazDeadSprites();
	for (int i = 0; i < spaz_dead_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(spaz_dead_sprites[i]));
	}
}

std::string Player::getPath(CharacterType character) {
	return this->image_path[character];
}


std::list<RectangularSprite>::iterator Player::img_coords(CharacterType character, CharacterStateEntity mov_type, int pjId) {
	if (mov_type != this->last_move[pjId]) {
		this->counts[pjId][mov_type] = 0;
		this->last_move[pjId] = mov_type;
	}
	std::list<RectangularSprite>::iterator it = this->sprites[character][mov_type].begin();
	for (int i = 0; i != this->counts[pjId][mov_type]; i++) {
		++it;
		if (it == this->sprites[character][mov_type].end()) {
			it = this->sprites[character][mov_type].begin();
		}
	}
	this->counts[pjId][mov_type]++;
	return it;
}

void Player::draw_players(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<CharacterType, SDL2pp::Texture*>& pjs_textures, std::vector<PlayerDTO>& players, int dir_x_screen, int dir_y_screen, uint32_t mainPlayerId) {
	int i = 0;
	int main_pj_x = 0;
	int main_pj_y = 0;
	int distance_main_secondary_x;
	int distance_main_secondary_y;
	for (auto p: players) {
		CharacterStateEntity mov_type = p.getState();
		int pjId = p.getPlayerId();
		if (!this->init) {
			this->last_move[pjId] = mov_type;
			this->counts[p.getPlayerId()][CharacterStateEntity::IDLE] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::MOVING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SPRINTING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SHOOTING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::JUMPING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SPECIAL_ATTACK] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::INTOXICATED] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::TAKING_DAMAGE] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::DEAD] = 0;

		}	
		std::list<RectangularSprite>::iterator it = img_coords(p.getType(), mov_type, pjId);
		int x = p.getX() * window.GetWidth() / 255;
		int y = static_cast<int>(p.getY());
		if (p.getPlayerId() == mainPlayerId) { //i == 0 es el player que ejecuto el codigo, cambiar por playerId
			if (dir_x_screen != 0) {
				main_pj_x = x;
				x = dir_x_screen;
			}
			if (dir_y_screen != 0) {
				main_pj_y = y;
				y = dir_y_screen;
			}
		} else {
			if (dir_x_screen != 0) { 
				distance_main_secondary_x = x - main_pj_x;
				x = dir_x_screen + distance_main_secondary_x;
			}
			if (dir_y_screen != 0) {
				distance_main_secondary_y = y - main_pj_y;
				y = dir_y_screen + distance_main_secondary_y;
			}
		}

		renderer.Copy(*pjs_textures[p.getType()], SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                      SDL2pp::Rect(x, y, this->width, this->height), 0.0, SDL2pp::NullOpt, flip);
        
		i++;
	}
	this->init = true;
}
