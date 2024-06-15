#include "enemy.h"
#include "../../Common/sprite.h"
#include "../../Common/DTO/enemy.h"
#include "../Common/Config/ClientConfig.h"

#include <iostream>


#include "enemyweapon.h"

enum type_enemies { Turtle, Schartzen, YellowMons };
enum actions { Walk, Attack, Death };

/*Solo que caminen*/

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


	/*
    this->path = "../assets/Enemies/Schwartzenguard.png";

    this->draw_width = 60;
    this->draw_height = 100;
    this->speed = 2;

    this->sprites[Walk].push_back(RectangularSprite(11, 6, 65, 56));
    this->sprites[Walk].push_back(RectangularSprite(79, 6, 59, 56));
    this->sprites[Walk].push_back(RectangularSprite(142, 6, 46, 56));
    this->sprites[Walk].push_back(RectangularSprite(190, 6, 53, 56));
    this->sprites[Walk].push_back(RectangularSprite(248, 6, 66, 56));
    this->sprites[Walk].push_back(RectangularSprite(316, 6, 73, 56));
    this->sprites[Walk].push_back(RectangularSprite(391, 6, 61, 56));
    this->sprites[Walk].push_back(RectangularSprite(452, 6, 53, 56));
    this->sprites[Walk].push_back(RectangularSprite(505, 6, 50, 56));
    this->sprites[Walk].push_back(RectangularSprite(555, 6, 67, 56));

    this->sprites[Attack].push_back(RectangularSprite(6, 67, 65, 60));
    this->sprites[Attack].push_back(RectangularSprite(71, 67, 65, 60));
    this->sprites[Attack].push_back(RectangularSprite(136, 67, 77, 60));
    this->sprites[Attack].push_back(RectangularSprite(213, 67, 96, 60));
    this->sprites[Attack].push_back(RectangularSprite(309, 67, 91, 60));
    this->sprites[Attack].push_back(RectangularSprite(400, 67, 98, 60));
    this->sprites[Attack].push_back(RectangularSprite(498, 67, 98, 60));
    this->sprites[Attack].push_back(RectangularSprite(10, 127, 95, 76));
    this->sprites[Attack].push_back(RectangularSprite(105, 127, 85, 76));
    this->sprites[Attack].push_back(RectangularSprite(190, 127, 93, 76));
    this->sprites[Attack].push_back(RectangularSprite(283, 127, 72, 76));
    this->sprites[Attack].push_back(RectangularSprite(355, 127, 72, 76));
    this->sprites[Attack].push_back(RectangularSprite(427, 127, 74, 76));
    this->sprites[Attack].push_back(RectangularSprite(501, 127, 64, 76));
    this->sprites[Attack].push_back(RectangularSprite(565, 127, 60, 76));
    this->sprites[Attack].push_back(RectangularSprite(10, 221, 85, 48));
    this->sprites[Attack].push_back(RectangularSprite(95, 221, 61, 48));


    this->sprites[Dead].push_back(RectangularSprite(384, 207, 41, 61));
    this->sprites[Dead].push_back(RectangularSprite(426, 207, 44, 61));
    this->sprites[Dead].push_back(RectangularSprite(470, 207, 61, 61));
    this->sprites[Dead].push_back(RectangularSprite(531, 207, 56, 61));
    this->sprites[Dead].push_back(RectangularSprite(531, 207, 56, 61));
    this->sprites[Dead].push_back(RectangularSprite(531, 207, 56, 61));
    this->sprites[Dead].push_back(RectangularSprite(531, 207, 56, 61));
    this->sprites[Dead].push_back(RectangularSprite(531, 207, 56, 61));
	*/

	/*
    this->path = "../assets/Enemies/Enemies.png";

    this->draw_width = 30;
    this->draw_height = 50;
    this->speed = 5;

    this->sprites[Walk].push_back(RectangularSprite(14, 9, 70, 66));
    this->sprites[Walk].push_back(RectangularSprite(93, 9, 62, 66));
    this->sprites[Walk].push_back(RectangularSprite(161, 9, 53, 66));
    this->sprites[Walk].push_back(RectangularSprite(214, 9, 77, 66));
    this->sprites[Walk].push_back(RectangularSprite(300, 9, 58, 66));
    this->sprites[Walk].push_back(RectangularSprite(365, 9, 60, 66));
    this->sprites[Walk].push_back(RectangularSprite(430, 9, 67, 66));
    this->sprites[Walk].push_back(RectangularSprite(505, 9, 70, 66));
    this->sprites[Walk].push_back(RectangularSprite(593, 9, 73, 66));
    this->sprites[Walk].push_back(RectangularSprite(675, 9, 70, 66));
    this->sprites[Walk].push_back(RectangularSprite(750, 9, 75, 66));
    this->sprites[Walk].push_back(RectangularSprite(830, 9, 77, 66));

    this->sprites[Attack].push_back(RectangularSprite(355, 75, 45, 78));
    this->sprites[Attack].push_back(RectangularSprite(410, 75, 60, 78));
    this->sprites[Attack].push_back(RectangularSprite(475, 75, 62, 78));
    this->sprites[Attack].push_back(RectangularSprite(542, 75, 60, 78));
    this->sprites[Attack].push_back(RectangularSprite(614, 75, 70, 78));
    this->sprites[Attack].push_back(RectangularSprite(695, 75, 46, 78));

    this->sprites[Dead].push_back(RectangularSprite(917, 10, 33, 63));
    this->sprites[Dead].push_back(RectangularSprite(953, 10, 36, 63));
    this->sprites[Dead].push_back(RectangularSprite(990, 10, 35, 63));
    this->sprites[Dead].push_back(RectangularSprite(1030, 10, 35, 63));
    this->sprites[Dead].push_back(RectangularSprite(1030, 10, 35, 63));
    this->sprites[Dead].push_back(RectangularSprite(1030, 10, 35, 63));
    this->sprites[Dead].push_back(RectangularSprite(1030, 10, 35, 63));
    this->sprites[Dead].push_back(RectangularSprite(1030, 10, 35, 63));
	*/
}

std::string Enemy::getPath(EnemyType enemy_type) { return this->enemies_path[enemy_type]; }


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


void Enemy::draw_enemy(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy, std::vector<EnemyDTO> enemies, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
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
    	std::list<RectangularSprite>::iterator it = enemy_img_coords(e.getType(), mov_type, enemyId);
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
        renderer.Copy(enemy, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                  SDL2pp::Rect(x, y, this->width_height[e.getType()][index_width], this->width_height[e.getType()][index_height]), 0.0,
                  SDL2pp::NullOpt, this->flip);

    }
    this->init = true;
}
