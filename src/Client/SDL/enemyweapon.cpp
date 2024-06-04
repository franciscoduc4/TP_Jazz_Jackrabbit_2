#include "enemyweapon.h"

#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"

enum weapon_type { NoneWeapon, MangualWeapon, BombWeapon };

EnemyWeapon::EnemyWeapon(int enemy_weapon) {
	switch (enemy_weapon) {
		case NoneWeapon:
			this->x = -1;
			this->y = -1;
			this->width = 0;
			this->height = 0;
			this->speed = 0;
			this->activated = false;
			this->count = 0;
			this->flip = 0;
			break;
		
		case MangualWeapon:		
			this->x = -1;
			this->y = -1;
			this->width = 30;
			this->height = 20;
			this->speed = 10;
			this->sprites.push_back(RectangularSprite(408, 269, 51, 28));
			this->sprites.push_back(RectangularSprite(459, 269, 49, 28));
			this->sprites.push_back(RectangularSprite(508, 269, 55, 28));
			this->sprites.push_back(RectangularSprite(563, 269, 49, 28));
			this->activated = false;
			this->count = 0;
			this->flip = 0;
			break;
		case BombWeapon:
			break;
	}
}

void EnemyWeapon::activate(int pos_x, int pos_y, int flip) {
    if (this->speed != 0) {
        this->x = pos_x;
        this->y = pos_y;
        this->flip = flip;
        this->activated = true;
    }
}

std::list<Sprite>::iterator EnemyWeapon::weapon_coords() {
    std::list<Sprite>::iterator it = this->sprites.begin();
    for (int i = 0; i < this->count; i++) {
        ++it;
        if (it == this->sprites.end()) {
            it = this->sprites.begin();
        }
    }
    return it;
}

bool EnemyWeapon::draw_weapon(SDL2pp::Renderer& renderer, SDL2pp::Texture& weapon) {
    if (this->activated) {
        std::list<Sprite>::iterator it = weapon_coords();
        int weapon_pixel_x = it->x;
        int weapon_pixel_w = it->width;
        int weapon_pixel_y = it->y;
        int weapon_pixel_h = it->height;

        renderer.Copy(weapon,
                      SDL2pp::Rect(weapon_pixel_x, weapon_pixel_y, weapon_pixel_w, weapon_pixel_h),
                      SDL2pp::Rect(this->x, this->y, this->width, this->height), 0.0,
                      SDL2pp::NullOpt, this->flip);
					  
std::list<RectangularSprite>::iterator EnemyWeapon::weapon_coords() {
	std::list<RectangularSprite>::iterator it = this->sprites.begin();
	for (int i = 0; i < this->count; i++) {
		++it;
		if (it == this->sprites.end()) {
			it = this->sprites.begin();
		}

        if (this->x > 800 || this->x < 0) {  // WIDTH DE PANTALLA HARDCODEADO
            this->activated = false;
            this->x = -1;
            this->y = -1;
        } else {
            this->x += (this->flip == 0) ? this->speed : -this->speed;
        }
        this->count++;
    }
    return this->activated;
}
