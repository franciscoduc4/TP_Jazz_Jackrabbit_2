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
	/*
	int index_x = 0;
	int index_y = 1;
	int index_width = 3;
	int index_height = 4;
	*/
	this->width = 50;
	this->height = 80;
	this->flip = 0;
	this->init = false;
	
	this->image_path[CharacterType::JAZZ] = "../assets/Characters/Jazz.png";
	/*
	std::vector<std::vector<int>> CharacterStateEntity::MOVING_sprites = ClientConfig::getJazzCharacterStateEntity::MOVINGingSprites();
	for (int i = 0; i < CharacterStateEntity::MOVING_sprites.size(); i++) {
		this->sprites[aCharacterStateEntity::MOVING].push_back(RectangularSprite(CharacterStateEntity::MOVING_sprites[CharacterType::LORI][i][index_x], CharacterStateEntity::MOVING_sprites[CharacterType::LORI][i][index_y], CharacterStateEntity::MOVING_sprites[CharacterType::LORI][i][index_width], CharacterStateEntity::MOVING_sprites[CharacterType::LORI][i][index_height]));
	}

				
	std::vector<std::vector<int>> CharacterStateEntity::SPRINTINGning_sprites = ClientConfig::getJazzCharacterStateEntity::SPRINTINGningSprites();
	for (int i = 0; i < CharacterStateEntity::SPRINTINGning_sprites.size(); i++) {
		this->sprites[aCharacterStateEntity::SPRINTING].push_back(RectangularSprite(CharacterStateEntity::SPRINTINGning_sprites[CharacterType::LORI][i][index_x], CharacterStateEntity::SPRINTINGning_sprites[CharacterType::LORI][i][index_y], CharacterStateEntity::SPRINTINGning_sprites[CharacterType::LORI][i][index_width], CharacterStateEntity::SPRINTINGning_sprites[CharacterType::LORI][i][index_height]));
	}
	
	std::vector<std::vector<int>> CharacterStateEntity::SHOOTING_sprites = ClientConfig::getJazzCharacterStateEntity::SHOOTINGingSprites();
	for (int i = 0; i < CharacterStateEntity::SHOOTING_sprites.size(); i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(CharacterStateEntity::SHOOTING_sprites[CharacterType::LORI][i][index_x], CharacterStateEntity::SHOOTING_sprites[CharacterType::LORI][i][index_y], CharacterStateEntity::SHOOTING_sprites[CharacterType::LORI][i][index_width], CharacterStateEntity::SHOOTING_sprites[CharacterType::LORI][i][index_height]));
	}
	
	std::vector<std::vector<int>> CharacterStateEntity::JUMPING_sprites = ClientConfig::getJazzCharacterStateEntity::JUMPINGingSprites();
	for (int i = 0; i < CharacterStateEntity::JUMPING_sprites.size(); i++) {
		this->sprites[aCharacterStateEntity::JUMPING].push_back(RectangularSprite(CharacterStateEntity::JUMPING_sprites[CharacterType::LORI][i][index_x], CharacterStateEntity::JUMPING_sprites[CharacterType::LORI][i][index_y], CharacterStateEntity::JUMPING_sprites[CharacterType::LORI][i][index_width], CharacterStateEntity::JUMPING_sprites[CharacterType::LORI][i][index_height]));
	}
	
	std::vector<std::vector<int>> dash_sprites = ClientConfig::getJazzDashingSprites();
	for (int i = 0; i < dash_sprites.size(); i++) {
		this->sprites[aDash].push_back(RectangularSprite(dash_sprites[CharacterType::LORI][i][index_x], dash_sprites[CharacterType::LORI][i][index_y], dash_sprites[CharacterType::LORI][i][index_width], dash_sprites[CharacterType::LORI][i][index_height]));
	}
	*/
	
	for (int i = 0; i < 8; i++) {
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::MOVING].push_back(RectangularSprite(57 * i, 790, 57, 46));
		this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(67 * i, 853, 67, 39));
	}
	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(0, 557, 47, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(51, 557, 45, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(101, 557, 36, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(143, 557, 37, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(185, 557, 36, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(226, 557, 39, 57));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(265, 557, 54, 57));			

	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(0, 1197, 50, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(53, 1197, 36, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(89, 1197, 43, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(132, 1197, 46, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(178, 1197, 48, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(226, 1197, 52, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(278, 1197, 51, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(329, 1197, 53, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(383, 1197, 45, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(429, 1197, 36, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(465, 1197, 35, 60));	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(500, 1197, 37, 60));	
	/* 
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(0, 909, 45, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(45, 909, 43, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(90, 909, 45, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(135, 909, 52, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(188, 909, 55, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(243, 909, 53, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(295, 909, 65, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(360, 909, 66, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(426, 909, 68, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(495, 909, 67, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(562, 909, 67, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(629, 909, 61, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(690, 909, 58, 65));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(0, 993, 70, 41));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(72, 993, 64, 41));
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(137, 993, 69, 41));			
	this->sprites[CharacterType::JAZZ][Dash].push_back(RectangularSprite(207, 993, 69, 41));
	*/
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(0, 715, 56, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(57, 715, 54, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(112, 715, 46, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(159, 715, 43, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(202, 715, 36, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(239, 715, 31, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(270, 715, 29, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(300, 715, 27, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(328, 715, 25, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(354, 715, 28, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(387, 715, 42, 58));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(429, 715, 51, 58));
	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(0, 2228, 60, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(60, 2228, 60, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(120, 2228, 60, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(180, 2228, 63, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(243, 2228, 67, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(310, 2228, 66, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(376, 2228, 64, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(440, 2228, 60, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(500, 2228, 60, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(560, 2228, 62, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(622, 2228, 63, 55));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(685, 2228, 60, 55));
	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(0, 3011, 42, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(42, 3011, 40, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(82, 3011, 40, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(122, 3011, 48, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(170, 3011, 50, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(225, 3011, 60, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(292, 3011, 70, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(365, 3011, 73, 62));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(443, 3011, 70, 62));
	
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 3090, 50, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(50, 3090, 45, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(95, 3090, 80, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(175, 3090, 85, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(270, 3090, 90, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(370, 3090, 90, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(468, 3090, 95, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(568, 3090, 92, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(665, 3090, 90, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(760, 3090, 75, 74));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 3166, 48, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(48, 3166, 50, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(98, 3166, 60, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(158, 3166, 66, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(230, 3166, 66, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(300, 3166, 62, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(370, 3166, 72, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(450, 3166, 84, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(540, 3166, 80, 64));
	this->sprites[CharacterType::JAZZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(625, 3166, 65, 64));
	/* 
	this->sprites[CharacterType::JAZZ][Liveicon].push_back(RectangularSprite(0, 3246, 40, 43));
	this->sprites[CharacterType::JAZZ][Liveicon].push_back(RectangularSprite(50, 3246, 42, 43));
	this->sprites[CharacterType::JAZZ][Liveicon].push_back(RectangularSprite(92, 3246, 40, 43));
	this->sprites[CharacterType::JAZZ][Liveicon].push_back(RectangularSprite(132, 3246, 40, 43));
	this->sprites[CharacterType::JAZZ][Liveicon].push_back(RectangularSprite(172, 3246, 40, 43));
	*/	
			
		
	this->image_path[CharacterType::LORI] = "../assets/Characters/Lori.png";
				
	for (int i = 0; i < 8; i++) {
		this->sprites[CharacterType::LORI][CharacterStateEntity::MOVING].push_back(RectangularSprite(51 * i, 556, 51, 51));
		this->sprites[CharacterType::LORI][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(55 * i, 626, 55, 42));
	}
	
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(0, 341, 48, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(50, 341, 43, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(100, 341, 38, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(140, 341, 37, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(180, 341, 40, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(220, 341, 40, 56));

	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(0, 963, 48, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(50, 963, 45, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(98, 963, 44, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(145, 963, 45, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(190, 963, 45, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(235, 963, 52, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(288, 963, 52, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(340, 963, 52, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(392, 963, 53, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(445, 963, 37, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(485, 963, 40, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(525, 963, 40, 70));	
	this->sprites[CharacterType::LORI][CharacterStateEntity::JUMPING].push_back(RectangularSprite(565, 963, 40, 70));	

	/* 
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(0, 684, 45, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(45, 684, 44, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(89, 684, 46, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(135, 684, 44, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(179, 684, 49, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(228, 684, 49, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(277, 684, 44, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(321, 684, 59, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(380, 684, 55, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(435, 684, 57, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(492, 684, 60, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(552, 684, 68, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(620, 684, 60, 57));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(0, 760, 64, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(64, 760, 64, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(128, 760, 65, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(193, 760, 67, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(260, 760, 64, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(324, 760, 65, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(391, 760, 65, 45));
	this->sprites[CharacterType::LORI][Dash].push_back(RectangularSprite(456, 760, 65, 45));
 	*/	
	
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(0, 485, 50, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(50, 485, 50, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(100, 485, 40, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(143, 485, 46, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(190, 485, 48, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(240, 485, 50, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(295, 485, 55, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(355, 485, 65, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(420, 485, 68, 60));
	this->sprites[CharacterType::LORI][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(490, 485, 63, 60));
	
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(0, 1964, 52, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(52, 1964, 53, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(105, 1964, 54, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(159, 1964, 53, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(212, 1964, 53, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(265, 1964, 53, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(318, 1964, 52, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(370, 1964, 50, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(420, 1964, 50, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(470, 1964, 53, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(523, 1964, 51, 56));
	this->sprites[CharacterType::LORI][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(574, 1964, 56, 56));
	
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(0, 2656, 51, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(51, 2656, 46, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(97, 2656, 39, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(136, 2656, 46, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(182, 2656, 54, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(236, 2656, 60, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(296, 2656, 54, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(350, 2656, 55, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(405, 2656, 47, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(452, 2656, 46, 59));
	this->sprites[CharacterType::LORI][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(498, 2656, 42, 59));
	
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 2729, 51, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(51, 2729, 49, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(100, 2729, 71, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(171, 2729, 133, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(304, 2729, 188, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(492, 2729, 240, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(732, 2729, 112, 92));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 2826, 51, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(71, 2826, 71, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(142, 2826, 75, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(217, 2826, 75, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(292, 2826, 58, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(350, 2826, 50, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(400, 2826, 48, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(448, 2826, 37, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(485, 2826, 48, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(533, 2826, 47, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(580, 2826, 48, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(628, 2826, 35, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(663, 2826, 42, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(705, 2826, 45, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(750, 2826, 46, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(796, 2826, 49, 65));
	this->sprites[CharacterType::LORI][CharacterStateEntity::DEAD].push_back(RectangularSprite(845, 2826, 49, 65));
	
	/* this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(0, 2906, 43, 49));
	this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(43, 2906, 45, 49));
	this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(88, 2906, 46, 49));
	this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(134, 2906, 46, 49));
	this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(180, 2906, 45, 49));
	this->sprites[CharacterType::LORI][Liveicon].push_back(RectangularSprite(225, 2906, 45, 49));
	 */		
	this->image_path[CharacterType::SPAZ] = "../assets/Characters/Spaz.png";

	for (int i = 0; i < 8; i++) {
		this->sprites[CharacterType::SPAZ][CharacterStateEntity::MOVING].push_back(RectangularSprite(50 * i, 747, 50, 45));
	}
	
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(0, 807, 48, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(48, 807, 58, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(106, 807, 52, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(160, 807, 48, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(210, 807, 48, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(260, 807, 54, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(315, 807, 50, 40));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPRINTING].push_back(RectangularSprite(366, 807, 50, 40));

	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(0, 539, 52, 48));		
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(53, 539, 50, 48));		
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(105, 539, 48, 48));		
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(153, 539, 36, 48));		
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(190, 539, 42, 48));		
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SHOOTING].push_back(RectangularSprite(232, 539, 47, 48));		

	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(0, 1139, 44, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(44, 1139, 36, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(81, 1139, 40, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(122, 1139, 42, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(165, 1139, 38, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(205, 1139, 40, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(245, 1139, 40, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(287, 1139, 43, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(330, 1139, 45, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(378, 1139, 34, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(415, 1139, 33, 55));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::JUMPING].push_back(RectangularSprite(450, 1139, 34, 55));
	
	/*
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(0, 861, 40, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(40, 861, 50, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(90, 861, 48, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(138, 861, 53, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(191, 861, 53, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(244, 861, 56, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(300, 861, 60, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(360, 861, 66, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(426, 861, 63, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(489, 861, 63, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(552, 861, 67, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(619, 861, 65, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(684, 861, 47, 60));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(0, 936, 58, 44));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(58, 936, 53, 44));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(111, 936, 54, 44));
	this->sprites[CharacterType::SPAZ][Dash].push_back(RectangularSprite(165, 936, 55, 44));
	*/

	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(0, 681, 50, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(50, 681, 51, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(101, 681, 41, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(142, 681, 40, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(182, 681, 45, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(227, 681, 47, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(274, 681, 49, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(325, 681, 54, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(380, 681, 56, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(436, 681, 56, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(495, 681, 48, 48));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::SPECIAL_ATTACK].push_back(RectangularSprite(543, 681, 48, 48));
	
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(0, 2132, 41, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(41, 2132, 49, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(90, 2132, 42, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(132, 2132, 40, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(172, 2132, 48, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(220, 2132, 43, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(263, 2132, 42, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(305, 2132, 47, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(352, 2132, 48, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(400, 2132, 43, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(443, 2132, 47, 51));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::INTOXICATED].push_back(RectangularSprite(490, 2132, 45, 51));
	
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(0, 2915, 50, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(50, 2915, 50, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(100, 2915, 55, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(155, 2915, 70, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(225, 2915, 85, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(310, 2915, 80, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(400, 2915, 75, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(480, 2915, 70, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(550, 2915, 65, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(615, 2915, 60, 68));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::TAKING_DAMAGE].push_back(RectangularSprite(675, 2915, 50, 68));
	
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 3005, 80, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(80, 3005, 95, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(175, 3005, 95, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(270, 3005, 105, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(375, 3005, 95, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(470, 3005, 60, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(530, 3005, 30, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(560, 3005, 35, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(595, 3005, 40, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(635, 3005, 60, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(695, 3005, 85, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(785, 3005, 98, 74));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(0, 3105, 104, 69));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(115, 3105, 85, 69));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(212, 3105, 70, 69));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(287, 3105, 69, 69));
	this->sprites[CharacterType::SPAZ][CharacterStateEntity::DEAD].push_back(RectangularSprite(361, 3105, 48, 69));
	
	/*
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(0, 3202, 40, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(40, 3202, 37, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(77, 3202, 38, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(115, 3202, 38, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(153, 3202, 39, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(192, 3202, 38, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(230, 3202, 40, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(270, 3202, 37, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(307, 3202, 37, 42));
	this->sprites[CharacterType::SPAZ][Liveicon].push_back(RectangularSprite(344, 3202, 40, 42));
	*/
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

void Player::draw_players(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<CharacterType, SDL2pp::Texture*>& pjs_textures, std::vector<PlayerDTO>& players, int dir_x_screen, int dir_y_screen) {
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
			this->counts[p.getPlayerId()][CharacterStateEntity::MOVING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SPRINTING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SHOOTING] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::JUMPING] = 0;
			//this->counts[p.getPlayerId()][Dash] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::SPECIAL_ATTACK] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::INTOXICATED] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::TAKING_DAMAGE] = 0;
			this->counts[p.getPlayerId()][CharacterStateEntity::DEAD] = 0;
			//this->counts[p.getPlayerId()][Liveicon] = 0;

		}	
		std::list<RectangularSprite>::iterator it = img_coords(p.getType(), mov_type, pjId);
		int x = p.getX();
		int y = p.getY();
		if (i == 0) { //i == 0 es el player que ejecuto el codigo, cambiar por playerId
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




/*
void Player::CharacterStateEntity::SHOOTING(int x, int y, int flip) {
	
	Projectile p(0, x, y, flip);
	this->projectiles.push_back(p);
}


void Player::draw_projectiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile) {
	std::list<Projectile>::iterator it = this->projectiles.begin();
	
	while (it != this->projectiles.end()) {
		if (!it->draw_projectile(window, renderer, projectile)) {
			it = this->projectiles.erase(it);
		} else {
			++it;
		}
		
	}
}
*/
