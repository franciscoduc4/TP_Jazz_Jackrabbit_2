#include "projectile.h"
#include "../../Common/sprite.h"

#include <SDL2pp/SDL2pp.hh>


enum projectile_type { Normal, BlueBullet, VioletBullet, RedBomb, VioletBomb };

Projectile::Projectile(int p_type, int pos_x, int pos_y, int flip): x(pos_x), y(pos_y), flip(flip) {
	this->type = p_type;
	this->count = 0;
	
	this->y_fire = 45;
	this->x_fire = 48;
	this->width_fire = 15;
	this->height_fire = 12;	

	this->sprites[Normal].push_back(RectangularSprite(44, 36, 13, 7));
	this->sprites[Normal].push_back(RectangularSprite(58, 36, 13, 7));		
	this->sprites[Normal].push_back(RectangularSprite(73, 36, 13, 7));
			
	this->sprites[BlueBullet].push_back(RectangularSprite(144, 31, 12, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(156, 31, 13, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(169, 31, 11, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(180, 31, 10, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(190, 31, 10, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(200, 31, 10, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(210, 31, 11, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(221, 31, 13, 10));
	this->sprites[BlueBullet].push_back(RectangularSprite(234, 31, 11, 10));
			
	this->sprites[VioletBullet].push_back(RectangularSprite(139, 41, 14, 12));	
	this->sprites[VioletBullet].push_back(RectangularSprite(153, 41, 16, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(169, 41, 14, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(183, 41, 12, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(195, 41, 12, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(207, 41, 12, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(219, 41, 14, 12));
	this->sprites[VioletBullet].push_back(RectangularSprite(233, 41, 16, 12));
		
	/*
	this->sprites.push_back(RectangularSprite(83, 361, 18, 14));
	this->sprites.push_back(RectangularSprite(101, 361, 17, 14));
	this->sprites.push_back(RectangularSprite(118, 361, 15, 14));
	this->sprites.push_back(RectangularSprite(133, 361, 17, 14));
	this->sprites.push_back(RectangularSprite(150, 361, 15, 14));
	this->sprites.push_back(RectangularSprite(165, 361, 17, 14));
	this->sprites.push_back(RectangularSprite(182, 361, 15, 14));
	this->sprites.push_back(RectangularSprite(197, 361, 14, 14));
	this->sprites.push_back(RectangularSprite(211, 361, 16, 14));
	this->sprites.push_back(RectangularSprite(227, 361, 16, 14));
	*/
	
	this->sprites[RedBomb].push_back(RectangularSprite(286, 323, 23, 8));
	this->sprites[RedBomb].push_back(RectangularSprite(309, 323, 24, 8));
	this->sprites[RedBomb].push_back(RectangularSprite(333, 323, 24, 8));
		
	/*
	this->sprites.push_back(RectangularSprite(83, 377, 18, 14));
	this->sprites.push_back(RectangularSprite(101, 377, 17, 14));
	this->sprites.push_back(RectangularSprite(118, 377, 15, 14));
	this->sprites.push_back(RectangularSprite(133, 377, 17, 14));
	this->sprites.push_back(RectangularSprite(150, 377, 15, 14));
	this->sprites.push_back(RectangularSprite(165, 377, 17, 14));
	this->sprites.push_back(RectangularSprite(182, 377, 15, 14));
	this->sprites.push_back(RectangularSprite(197, 377, 14, 14));
	this->sprites.push_back(RectangularSprite(211, 377, 16, 14));
	this->sprites.push_back(RectangularSprite(227, 377, 16, 14));
	*/
	this->sprites[VioletBomb].push_back(RectangularSprite(286, 137, 23, 8));
	this->sprites[VioletBomb].push_back(RectangularSprite(309, 137, 24, 8));
	this->sprites[VioletBomb].push_back(RectangularSprite(333, 137, 24, 8));			
}

std::list<RectangularSprite>::iterator Projectile::img_coords() {
	//Modificar que se pueda cambiar de bala
	std::list<RectangularSprite>::iterator it = this->sprites[Normal].begin();
	for (int i = 0; i != this->count; i++) {
		++it;
		if (it == this->sprites[Normal].end()) {
			it = this->sprites[Normal].begin();
		}
		
	}
	this->count++;
	return it;

}
bool Projectile::draw_projectile(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile, std::vector<BulletDTO>& bullets) {
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
		std::list<RectangularSprite>::iterator it2 = img_coords(); 
		proj_pixel_x = it2->getX();
		proj_pixel_w = it2->getWidth();	
		proj_pixel_y = it2->getY();
		proj_pixel_h = it2->getHeight();	
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
		
	if (this->x < 0 || this->x > window.GetWidth() || this->y < 0 || this->y > window.GetHeight()) {
		return false;
	}
	return true;
}



