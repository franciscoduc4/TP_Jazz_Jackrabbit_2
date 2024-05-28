#include "enemy.h"
#include "../sprite.h"
#include "enemyweapon.h"

enum type_enemies { Turtle, Schartzen, YellowMons };
enum actions { Walk, Attack, Death };

Enemy::Enemy(int enemy, int x, int y): pos_x(x), pos_y(y), weapon(enemy) {
	this->count = 0;
	this->flip = 0;
	switch(enemy) {
		case Turtle:
			this->path = "../assets/Enemies/TurtleEnemies.png";
			
			this->draw_width = 50;
			this->draw_height = 50;
			this->speed = 1;
			
			this->sprites[Walk].push_back(Sprite(12, 56, 67, 56));
			this->sprites[Walk].push_back(Sprite(80, 56, 69, 56));			
			this->sprites[Walk].push_back(Sprite(150, 56, 68, 56));			
			this->sprites[Walk].push_back(Sprite(220, 56, 66, 56));
			this->sprites[Walk].push_back(Sprite(290, 56, 68, 56));
			this->sprites[Walk].push_back(Sprite(360, 56, 61, 56));			
			this->sprites[Walk].push_back(Sprite(422, 56, 65, 56));
			this->sprites[Walk].push_back(Sprite(487, 56, 65, 56));			
			this->sprites[Walk].push_back(Sprite(555, 56, 61, 56));			
			this->sprites[Walk].push_back(Sprite(616, 56, 63, 56));			
			this->sprites[Walk].push_back(Sprite(680, 56, 66, 56));			
			this->sprites[Walk].push_back(Sprite(746, 56, 68, 56));			
			
			this->sprites[Attack].push_back(Sprite(5, 120, 58, 50));
			this->sprites[Attack].push_back(Sprite(63, 120, 60, 50));
			this->sprites[Attack].push_back(Sprite(123, 120, 60, 50));
			this->sprites[Attack].push_back(Sprite(183, 120, 77, 50));
			this->sprites[Attack].push_back(Sprite(260, 120, 95, 50));
			this->sprites[Attack].push_back(Sprite(357, 120, 99, 50));
			this->sprites[Attack].push_back(Sprite(458, 120, 114, 50));
			this->sprites[Attack].push_back(Sprite(572, 120, 120, 50));
			this->sprites[Attack].push_back(Sprite(692, 120, 114, 50));
			this->sprites[Attack].push_back(Sprite(809, 120, 84, 50));
			this->sprites[Attack].push_back(Sprite(893, 120, 60, 50));

			this->sprites[Death].push_back(Sprite(384, 9, 75, 42));
			this->sprites[Death].push_back(Sprite(460, 9, 70, 42));
			this->sprites[Death].push_back(Sprite(530, 9, 62, 42));
			this->sprites[Death].push_back(Sprite(592, 9, 52, 42));
			this->sprites[Death].push_back(Sprite(644, 9, 47, 42));
			this->sprites[Death].push_back(Sprite(691, 9, 42, 42));
			
			
			break;
		case Schartzen: 
			this->path = "../assets/Enemies/Schwartzenguard.png";
			
			this->draw_width = 60;
			this->draw_height = 100;
			this->speed = 2;

			this->sprites[Walk].push_back(Sprite(11, 6, 65, 56));
			this->sprites[Walk].push_back(Sprite(79, 6, 59, 56));
			this->sprites[Walk].push_back(Sprite(142, 6, 46, 56));
			this->sprites[Walk].push_back(Sprite(190, 6, 53, 56));
			this->sprites[Walk].push_back(Sprite(248, 6, 66, 56));
			this->sprites[Walk].push_back(Sprite(316, 6, 73, 56));
			this->sprites[Walk].push_back(Sprite(391, 6, 61, 56));
			this->sprites[Walk].push_back(Sprite(452, 6, 53, 56));
			this->sprites[Walk].push_back(Sprite(505, 6, 50, 56));
			this->sprites[Walk].push_back(Sprite(555, 6, 67, 56));
			
			this->sprites[Attack].push_back(Sprite(6, 67, 65, 60));
			this->sprites[Attack].push_back(Sprite(71, 67, 65, 60));
			this->sprites[Attack].push_back(Sprite(136, 67, 77, 60));
			this->sprites[Attack].push_back(Sprite(213, 67, 96, 60));
			this->sprites[Attack].push_back(Sprite(309, 67, 91, 60));
			this->sprites[Attack].push_back(Sprite(400, 67, 98, 60));
			this->sprites[Attack].push_back(Sprite(498, 67, 98, 60));
			this->sprites[Attack].push_back(Sprite(10, 127, 95, 76));
			this->sprites[Attack].push_back(Sprite(105, 127, 85, 76));
			this->sprites[Attack].push_back(Sprite(190, 127, 93, 76));
			this->sprites[Attack].push_back(Sprite(283, 127, 72, 76));
			this->sprites[Attack].push_back(Sprite(355, 127, 72, 76));
			this->sprites[Attack].push_back(Sprite(427, 127, 74, 76));
			this->sprites[Attack].push_back(Sprite(501, 127, 64, 76));
			this->sprites[Attack].push_back(Sprite(565, 127, 60, 76));
			this->sprites[Attack].push_back(Sprite(10, 221, 85, 48));
			this->sprites[Attack].push_back(Sprite(95, 221, 61, 48));
			
			
			this->sprites[Death].push_back(Sprite(384, 207, 41, 61));			
			this->sprites[Death].push_back(Sprite(426, 207, 44, 61));
			this->sprites[Death].push_back(Sprite(470, 207, 61, 61));
			this->sprites[Death].push_back(Sprite(531, 207, 56, 61));			
			this->sprites[Death].push_back(Sprite(531, 207, 56, 61));
			this->sprites[Death].push_back(Sprite(531, 207, 56, 61));
			this->sprites[Death].push_back(Sprite(531, 207, 56, 61));
			this->sprites[Death].push_back(Sprite(531, 207, 56, 61));
			
			
			break;
			
		case YellowMons:
			this->path = "../assets/Enemies/Enemies.png";
			
			this->draw_width = 30;
			this->draw_height = 50;
			this->speed = 5;
			
			this->sprites[Walk].push_back(Sprite(14, 9, 70, 66));
			this->sprites[Walk].push_back(Sprite(93, 9, 62, 66));
			this->sprites[Walk].push_back(Sprite(161, 9, 53, 66));
			this->sprites[Walk].push_back(Sprite(214, 9, 77, 66));
			this->sprites[Walk].push_back(Sprite(300, 9, 58, 66));
			this->sprites[Walk].push_back(Sprite(365, 9, 60, 66));
			this->sprites[Walk].push_back(Sprite(430, 9, 67, 66));
			this->sprites[Walk].push_back(Sprite(505, 9, 70, 66));
			this->sprites[Walk].push_back(Sprite(593, 9, 73, 66));
			this->sprites[Walk].push_back(Sprite(675, 9, 70, 66));
			this->sprites[Walk].push_back(Sprite(750, 9, 75, 66));
			this->sprites[Walk].push_back(Sprite(830, 9, 77, 66));
			
			this->sprites[Attack].push_back(Sprite(355, 75, 45, 78));
			this->sprites[Attack].push_back(Sprite(410, 75, 60, 78));			
			this->sprites[Attack].push_back(Sprite(475, 75, 62, 78));			
			this->sprites[Attack].push_back(Sprite(542, 75, 60, 78));			
			this->sprites[Attack].push_back(Sprite(614, 75, 70, 78));			
			this->sprites[Attack].push_back(Sprite(695, 75, 46, 78));			

			this->sprites[Death].push_back(Sprite(917, 10, 33, 63));			
			this->sprites[Death].push_back(Sprite(953, 10, 36, 63));
			this->sprites[Death].push_back(Sprite(990, 10, 35, 63));
			this->sprites[Death].push_back(Sprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(Sprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(Sprite(1030, 10, 35, 63));						
			this->sprites[Death].push_back(Sprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(Sprite(1030, 10, 35, 63));		
			
			
			break;
	}
}

std::string Enemy::getPath() {
	return this->path;
}


std::list<Sprite>::iterator Enemy::enemy_img_coords(int mov_type, int num_mov) {
	std::list<Sprite>::iterator it = this->sprites[mov_type].begin();
	for (int i = 0; i != num_mov; i++) {
		++it;
		if (it == this->sprites[mov_type].end()) {
			it = this->sprites[mov_type].begin();
		}
	}
	this->count++;
	return it;
}


void Enemy::draw_enemy(SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy, int mov_type) {
	if (this->count == 17 && mov_type == 1) {
		this->weapon.activate((this->flip == 0) ? this->pos_x + this->draw_width : this->pos_x, this->pos_y + this->draw_height / 2, this->flip);	
	}
	std::list<Sprite>::iterator it = enemy_img_coords(mov_type, this->count); 
	int enemy_pixel_x = it->x;
	int enemy_pixel_w = it->width;
	int enemy_pixel_y = it->y;
	int enemy_pixel_h = it->height;

	renderer.Copy(enemy, SDL2pp::Rect(enemy_pixel_x, enemy_pixel_y, enemy_pixel_w, enemy_pixel_h), SDL2pp::Rect(this->pos_x, this->pos_y, this->draw_width, this->draw_height), 0.0, SDL2pp::NullOpt, this->flip);
	
	if (!this->weapon.draw_weapon(renderer, enemy) && this->count > 17) {
		this->count = 0;
	}
	
	if (this->pos_x + this->speed > 800 - this->draw_width || this->pos_x + this->speed < 0) { //WIDTH DE PANTALLA HARDCODEADO
		this->speed *= -1;
		this->flip = (this->flip == 0) ? 1 : 0;
	} 
	this->pos_x += this->speed;
	
	
}
