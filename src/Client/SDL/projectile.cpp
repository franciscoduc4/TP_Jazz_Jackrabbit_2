#include "projectile.h"
#include "../sprite.h"

#include <SDL2pp/SDL2pp.hh>


enum projectile_type { Normal, BlueBullet, VioletBullet, RedBomb, VioletBomb };

Projectile::Projectile(int p_type, int pos_x, int pos_y, int flip): x(pos_x), y(pos_y), flip(flip) {
	this->type = p_type;
	this->count = 0;
	switch (p_type) {
		case Normal:
			this->sprites.push_back(Sprite(44, 36, 13, 7));
			this->sprites.push_back(Sprite(58, 36, 13, 7));		
			this->sprites.push_back(Sprite(73, 36, 13, 7));
			this->y_fire = 45;
			this->x_fire = 48;
			this->width_fire = 15;
			this->height_fire = 12;	
			
			break;
		case BlueBullet:
			this->sprites.push_back(Sprite(144, 31, 12, 10));
			this->sprites.push_back(Sprite(156, 31, 13, 10));
			this->sprites.push_back(Sprite(169, 31, 11, 10));
			this->sprites.push_back(Sprite(180, 31, 10, 10));
			this->sprites.push_back(Sprite(190, 31, 10, 10));
			this->sprites.push_back(Sprite(200, 31, 10, 10));
			this->sprites.push_back(Sprite(210, 31, 11, 10));
			this->sprites.push_back(Sprite(221, 31, 13, 10));
			this->sprites.push_back(Sprite(234, 31, 11, 10));
			this->y_fire = 45;
			this->x_fire = 48;
			this->width_fire = 15;
			this->height_fire = 12;	
			
			break;
			
		case VioletBullet:
			this->sprites.push_back(Sprite(139, 41, 14, 12));	
			this->sprites.push_back(Sprite(153, 41, 16, 12));
			this->sprites.push_back(Sprite(169, 41, 14, 12));
			this->sprites.push_back(Sprite(183, 41, 12, 12));
			this->sprites.push_back(Sprite(195, 41, 12, 12));
			this->sprites.push_back(Sprite(207, 41, 12, 12));
			this->sprites.push_back(Sprite(219, 41, 14, 12));
			this->sprites.push_back(Sprite(233, 41, 16, 12));
			this->y_fire = 45;
			this->x_fire = 48;
			this->width_fire = 15;
			this->height_fire = 12;	
			
			break;
		
		case RedBomb:
			/*
			this->sprites.push_back(Sprite(83, 361, 18, 14));
			this->sprites.push_back(Sprite(101, 361, 17, 14));
			this->sprites.push_back(Sprite(118, 361, 15, 14));
			this->sprites.push_back(Sprite(133, 361, 17, 14));
			this->sprites.push_back(Sprite(150, 361, 15, 14));
			this->sprites.push_back(Sprite(165, 361, 17, 14));
			this->sprites.push_back(Sprite(182, 361, 15, 14));
			this->sprites.push_back(Sprite(197, 361, 14, 14));
			this->sprites.push_back(Sprite(211, 361, 16, 14));
			this->sprites.push_back(Sprite(227, 361, 16, 14));
			*/
			
			this->sprites.push_back(Sprite(286, 323, 23, 8));
			this->sprites.push_back(Sprite(309, 323, 24, 8));
			this->sprites.push_back(Sprite(333, 323, 24, 8));
			this->y_fire = 45;
			this->x_fire = 48;
			this->width_fire = 15;
			this->height_fire = 12;	
			
			break;
		
		case VioletBomb:
			/*
			this->sprites.push_back(Sprite(83, 377, 18, 14));
			this->sprites.push_back(Sprite(101, 377, 17, 14));
			this->sprites.push_back(Sprite(118, 377, 15, 14));
			this->sprites.push_back(Sprite(133, 377, 17, 14));
			this->sprites.push_back(Sprite(150, 377, 15, 14));
			this->sprites.push_back(Sprite(165, 377, 17, 14));
			this->sprites.push_back(Sprite(182, 377, 15, 14));
			this->sprites.push_back(Sprite(197, 377, 14, 14));
			this->sprites.push_back(Sprite(211, 377, 16, 14));
			this->sprites.push_back(Sprite(227, 377, 16, 14));
			*/
			this->sprites.push_back(Sprite(286, 137, 23, 8));
			this->sprites.push_back(Sprite(309, 137, 24, 8));
			this->sprites.push_back(Sprite(333, 137, 24, 8));			
			this->y_fire = 45;
			this->x_fire = 48;
			this->width_fire = 15;
			this->height_fire = 12;	
			
			break;
	}	

}

std::list<Sprite>::iterator Projectile::img_coords() {
	std::list<Sprite>::iterator it = this->sprites.begin();
	for (int i = 0; i != this->count; i++) {
		++it;
		if (it == this->sprites.end()) {
			it = this->sprites.begin();
		}
		
	}
	this->count++;
	return it;

}
bool Projectile::draw_projectile(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile) {
	int proj_pixel_x;
	int proj_pixel_w;
	int proj_pixel_y;
	int proj_pixel_h;		
	if (this->count == 0) {
		proj_pixel_x = this->x_fire;
		proj_pixel_w = this->width_fire;
		proj_pixel_y = this->y_fire;
		proj_pixel_h = this->height_fire;
		this->count++;
	} else {
		std::list<Sprite>::iterator it2 = img_coords(); 
		proj_pixel_x = it2->x;
		proj_pixel_w = it2->width;	
		proj_pixel_y = it2->y;
		proj_pixel_h = it2->height;	
	}		
	int proj_speed = 20;
	if (this->flip == 1) {
		proj_speed = -20;
	}
	double angle = 180.0;
	if (this->type == RedBomb || this->type == VioletBomb) {
		angle = 0.0;
	}
	renderer.Copy(projectile, SDL2pp::Rect(proj_pixel_x, proj_pixel_y, proj_pixel_w, proj_pixel_h), SDL2pp::Rect(this->x, this->y, 20, 10), angle, SDL2pp::NullOpt, this->flip);
		
	this->x += proj_speed;
		
	if (this->x < 0 || this->x > 800 || this->y < 0 || this->y > 500) {
		return false;
	}
	return true;
}



