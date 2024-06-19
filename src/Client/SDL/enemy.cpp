#include "enemy.h"
#include "../../Common/sprite.h"
#include "../../Common/DTO/enemy.h"
#include "../Common/Config/ClientConfig.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include <iostream>


#include "enemyweapon.h"

/*
ENEMY_IDLE,              
ENEMY_JUMPING,           
ENEMY_FLYING,            
ENEMY_RECEIVING_DAMAGE,  
ENEMY_DEAD,              
ENEMY_RESPAWNING         
*/

Enemy::Enemy() {
    this->flip = 0;
    this->init = false;

    this->enemies_path[EnemyType::TURTLE] = ClientConfig::getTurtleFile();// "../assets/Enemies/TurtleEnemies.png";

	std::vector<int> walking_enemy_w_h{ClientConfig::getTurtleWidth(), ClientConfig::getTurtleHeight()};
    this->width_height[EnemyType::TURTLE] = walking_enemy_w_h;
	
    std::vector<std::vector<int>> turtle_walking_sprites = ClientConfig::getTurtleWalkingSprites();
    for (int i = 0; i < turtle_walking_sprites.size(); i++) {
        this->sprites[EnemyType::TURTLE][EnemyStateEntity::ENEMY_WALKING].push_back(RectangularSprite(turtle_walking_sprites[i]));
    }

    std::vector<std::vector<int>> turtle_attacking_sprites = ClientConfig::getTurtleAttackingSprites();
    for (int i = 0; i < turtle_attacking_sprites.size(); i++) {
        this->sprites[EnemyType::TURTLE][EnemyStateEntity::ENEMY_ATTACKING].push_back(RectangularSprite(turtle_attacking_sprites[i]));
    }                

    std::vector<std::vector<int>> turtle_dying_sprites = ClientConfig::getTurtleDyingSprites();
    for (int i = 0; i < turtle_dying_sprites.size(); i++) {
        this->sprites[EnemyType::TURTLE][EnemyStateEntity::ENEMY_DEAD].push_back(RectangularSprite(turtle_dying_sprites[i]));
    }


    this->enemies_path[EnemyType::SCHWARZENGUARD] = ClientConfig::getSchguardFile();
	
    std::vector<int> sch_enemy_w_h{ClientConfig::getSchWidth(), ClientConfig::getSchHeight()};
    this->width_height[EnemyType::SCHWARZENGUARD] = sch_enemy_w_h;
	
    std::vector<std::vector<int>> sch_walking_sprites = ClientConfig::getSchwartzenguardWalkingSprites();
    for (int i = 0; i < sch_walking_sprites.size(); i++) {
        this->sprites[EnemyType::SCHWARZENGUARD][EnemyStateEntity::ENEMY_WALKING].push_back(RectangularSprite(sch_walking_sprites[i]));
    }

    std::vector<std::vector<int>> sch_attacking_sprites = ClientConfig::getSchwartzenguardAttackingSprites();
    for (int i = 0; i < sch_attacking_sprites.size(); i++) {
        this->sprites[EnemyType::SCHWARZENGUARD][EnemyStateEntity::ENEMY_ATTACKING].push_back(RectangularSprite(sch_attacking_sprites[i]));
    }                

    std::vector<std::vector<int>> sch_dying_sprites = ClientConfig::getSchwartzenguardDyingSprites();
    for (int i = 0; i < sch_dying_sprites.size(); i++) {
        this->sprites[EnemyType::SCHWARZENGUARD][EnemyStateEntity::ENEMY_DEAD].push_back(RectangularSprite(sch_dying_sprites[i]));
    }
    
    
    this->enemies_path[EnemyType::YELLOWMON] = ClientConfig::getYellowmonsFile();
	
    std::vector<int> yellow_enemy_w_h{ClientConfig::getYellowMonsWidth(), ClientConfig::getYellowMonsHeight()};
    this->width_height[EnemyType::YELLOWMON] = yellow_enemy_w_h;
	
    std::vector<std::vector<int>> yellow_walking_sprites = ClientConfig::getYellowMonsWalkingSprites();
    for (int i = 0; i < yellow_walking_sprites.size(); i++) {
        this->sprites[EnemyType::YELLOWMON][EnemyStateEntity::ENEMY_WALKING].push_back(RectangularSprite(yellow_walking_sprites[i]));
    }

    std::vector<std::vector<int>> yellow_attacking_sprites = ClientConfig::getYellowMonsAttackingSprites();
    for (int i = 0; i < yellow_attacking_sprites.size(); i++) {
        this->sprites[EnemyType::YELLOWMON][EnemyStateEntity::ENEMY_ATTACKING].push_back(RectangularSprite(yellow_attacking_sprites[i]));
    }                

    std::vector<std::vector<int>> yellow_dying_sprites = ClientConfig::getYellowMonsDyingSprites();
    for (int i = 0; i < yellow_dying_sprites.size(); i++) {
        this->sprites[EnemyType::YELLOWMON][EnemyStateEntity::ENEMY_DEAD].push_back(RectangularSprite(yellow_dying_sprites[i]));
    }

}

std::string Enemy::getPath(EnemyType enemy_type) { return this->enemies_path[enemy_type]; }

std::map<EnemyType, std::unique_ptr<SDL2pp::Texture>> Enemy::getEnemiesTextures(SDL2pp::Renderer& renderer) {
    std::map<EnemyType, std::unique_ptr<SDL2pp::Texture>> enemies;
    
    SDL_Surface* enemy_surf = IMG_Load(getPath(EnemyType::TURTLE).c_str());
    SDL2pp::Surface enemySurface(enemy_surf);
    enemySurface.SetColorKey(true, SDL_MapRGB(enemySurface.Get()->format, 0, 128, 255));
    enemies[EnemyType::TURTLE] = std::make_unique<SDL2pp::Texture>(renderer, enemySurface);

    return enemies;
}


std::list<RectangularSprite>::iterator Enemy::enemy_img_coords(EnemyType enemy_type, EnemyStateEntity mov_type, int enemyId) {
    if (mov_type != last_move[enemyId]) {
        this->counts[enemyId][mov_type] = 0;
		this->last_move[enemyId] = mov_type;
    }

    std::list<RectangularSprite>::iterator it = this->sprites[enemy_type][mov_type].begin();
    for (int i = 0; i != this->counts[enemyId][mov_type]; i++) {
        ++it;
        if (it == this->sprites[enemy_type][mov_type].end()) {
            it = this->sprites[enemy_type][mov_type].begin();
        }
    }
    this->counts[enemyId][mov_type]++;
    return it;
}


void Enemy::draw_enemy(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<EnemyType, std::unique_ptr<SDL2pp::Texture>>& textures_enemies, std::vector<EnemyDTO> enemies, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
	int index_width = 0;
	int index_height = 1;
	int mov_type = 0;
    int x; 
    int y;
    int distance_main_enemy_x;
    int distance_main_enemy_y;
    for (auto e : enemies) {
        EnemyStateEntity mov_type = e.getState();
		int enemyId = e.getEnemyId();
        if (!this->init) {
            this->last_move[enemyId] = mov_type;
			this->counts[enemyId][EnemyStateEntity::ENEMY_WALKING] = 0;
			this->counts[enemyId][EnemyStateEntity::ENEMY_ATTACKING] = 0;
			this->counts[enemyId][EnemyStateEntity::ENEMY_DEAD] = 0;
		}	
    	std::list<RectangularSprite>::iterator it = enemy_img_coords(e.getEnemyType(), mov_type, enemyId);
        x = e.getX();
		y = e.getY();
		
        if (dir_x_screen != 0) { 
            distance_main_enemy_x = x - player.getX();
            x = dir_x_screen + distance_main_enemy_x;
        }
        if (dir_y_screen != 0) {
            distance_main_enemy_y = y - player.getX();
            y = dir_y_screen + distance_main_enemy_y;
        }
        renderer.Copy(*textures_enemies[e.getEnemyType()], SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                  SDL2pp::Rect(x, y, this->width_height[e.getEnemyType()][index_width], this->width_height[e.getEnemyType()][index_height]), 0.0,
                  SDL2pp::NullOpt, this->flip);

    }
    this->init = true;
}
