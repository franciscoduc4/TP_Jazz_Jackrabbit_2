#include "enemy.h"
#include "../../Common/sprite.h"

#include "enemyweapon.h"

enum type_enemies { Turtle, Schartzen, YellowMons };
enum actions { Walk, Attack, Death };

/*Solo que caminen*/

Enemy::Enemy(int enemy, int x, int y): pos_x(x), pos_y(y), weapon(enemy) {
	this->count = 0;
	this->flip = 0;
	switch(enemy) {
		case Turtle:
			this->path = "../assets/Enemies/TurtleEnemies.png";
			
			this->draw_width = 50;
			this->draw_height = 50;
			this->speed = 1;
			
			this->sprites[Walk].push_back(RectangularSprite(12, 56, 67, 56));
			this->sprites[Walk].push_back(RectangularSprite(80, 56, 69, 56));			
			this->sprites[Walk].push_back(RectangularSprite(150, 56, 68, 56));			
			this->sprites[Walk].push_back(RectangularSprite(220, 56, 66, 56));
			this->sprites[Walk].push_back(RectangularSprite(290, 56, 68, 56));
			this->sprites[Walk].push_back(RectangularSprite(360, 56, 61, 56));			
			this->sprites[Walk].push_back(RectangularSprite(422, 56, 65, 56));
			this->sprites[Walk].push_back(RectangularSprite(487, 56, 65, 56));			
			this->sprites[Walk].push_back(RectangularSprite(555, 56, 61, 56));			
			this->sprites[Walk].push_back(RectangularSprite(616, 56, 63, 56));			
			this->sprites[Walk].push_back(RectangularSprite(680, 56, 66, 56));			
			this->sprites[Walk].push_back(RectangularSprite(746, 56, 68, 56));			
			
			this->sprites[Attack].push_back(RectangularSprite(5, 120, 58, 50));
			this->sprites[Attack].push_back(RectangularSprite(63, 120, 60, 50));
			this->sprites[Attack].push_back(RectangularSprite(123, 120, 60, 50));
			this->sprites[Attack].push_back(RectangularSprite(183, 120, 77, 50));
			this->sprites[Attack].push_back(RectangularSprite(260, 120, 95, 50));
			this->sprites[Attack].push_back(RectangularSprite(357, 120, 99, 50));
			this->sprites[Attack].push_back(RectangularSprite(458, 120, 114, 50));
			this->sprites[Attack].push_back(RectangularSprite(572, 120, 120, 50));
			this->sprites[Attack].push_back(RectangularSprite(692, 120, 114, 50));
			this->sprites[Attack].push_back(RectangularSprite(809, 120, 84, 50));
			this->sprites[Attack].push_back(RectangularSprite(893, 120, 60, 50));

			this->sprites[Death].push_back(RectangularSprite(384, 9, 75, 42));
			this->sprites[Death].push_back(RectangularSprite(460, 9, 70, 42));
			this->sprites[Death].push_back(RectangularSprite(530, 9, 62, 42));
			this->sprites[Death].push_back(RectangularSprite(592, 9, 52, 42));
			this->sprites[Death].push_back(RectangularSprite(644, 9, 47, 42));
			this->sprites[Death].push_back(RectangularSprite(691, 9, 42, 42));
			
			
			break;
		case Schartzen: 
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
			
			
			this->sprites[Death].push_back(RectangularSprite(384, 207, 41, 61));			
			this->sprites[Death].push_back(RectangularSprite(426, 207, 44, 61));
			this->sprites[Death].push_back(RectangularSprite(470, 207, 61, 61));
			this->sprites[Death].push_back(RectangularSprite(531, 207, 56, 61));			
			this->sprites[Death].push_back(RectangularSprite(531, 207, 56, 61));
			this->sprites[Death].push_back(RectangularSprite(531, 207, 56, 61));
			this->sprites[Death].push_back(RectangularSprite(531, 207, 56, 61));
			this->sprites[Death].push_back(RectangularSprite(531, 207, 56, 61));
			
			
			break;
			
		case YellowMons:
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

			this->sprites[Death].push_back(RectangularSprite(917, 10, 33, 63));			
			this->sprites[Death].push_back(RectangularSprite(953, 10, 36, 63));
			this->sprites[Death].push_back(RectangularSprite(990, 10, 35, 63));
			this->sprites[Death].push_back(RectangularSprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(RectangularSprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(RectangularSprite(1030, 10, 35, 63));						
			this->sprites[Death].push_back(RectangularSprite(1030, 10, 35, 63));
			this->sprites[Death].push_back(RectangularSprite(1030, 10, 35, 63));		
			
			
			break;
	}
}

std::string Enemy::getPath() {
	return this->path;
}


std::list<RectangularSprite>::iterator Enemy::enemy_img_coords(int mov_type, int num_mov) {
	std::list<RectangularSprite>::iterator it = this->sprites[mov_type].begin();
	for (int i = 0; i != num_mov; i++) {
		++it;
		if (it == this->sprites[mov_type].end()) {
			it = this->sprites[mov_type].begin();
		}
	}
	this->count++;
	return it;
}


void Enemy::draw_enemy(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy, int mov_type) {
	if (this->count == 17 && mov_type == 1) {
		this->weapon.activate((this->flip == 0) ? this->pos_x + this->draw_width : this->pos_x, this->pos_y + this->draw_height / 2, this->flip);	
	}
	std::list<RectangularSprite>::iterator it = enemy_img_coords(mov_type, this->count); 
	int enemy_pixel_x = it->getX();
	int enemy_pixel_w = it->getWidth();
	int enemy_pixel_y = it->getY();
	int enemy_pixel_h = it->getHeight();

	renderer.Copy(enemy, SDL2pp::Rect(enemy_pixel_x, enemy_pixel_y, enemy_pixel_w, enemy_pixel_h), SDL2pp::Rect(this->pos_x, this->pos_y, this->draw_width, this->draw_height), 0.0, SDL2pp::NullOpt, this->flip);
	
	if (!this->weapon.draw_weapon(window, renderer, enemy) && this->count > 17) {
		this->count = 0;
	}
	
	if (this->pos_x + this->speed > window.GetWidth() - this->draw_width || this->pos_x + this->speed < 0) { //WIDTH DE PANTALLA HARDCODEADO
		this->speed *= -1;
		this->flip = (this->flip == 0) ? 1 : 0;
	} 
	this->pos_x += this->speed;
	
	
}
