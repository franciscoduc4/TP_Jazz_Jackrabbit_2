#include "projectile.h"
#include "../../Common/sprite.h"
#include "../Common/Config/ClientConfig.h"

#include <SDL2pp/SDL2pp.hh>


enum projectile_type { Normal, BlueBullet, VioletBullet, RedBomb, VioletBomb };

Projectile::Projectile(int p_type) {
	this->type = p_type;
	
	this->x_fire = ClientConfig::getFireX();
	this->y_fire = ClientConfig::getFireY();
	this->width_fire = ClientConfig::getFireWidth();
	this->height_fire = ClientConfig::getFireHeight();
	
	this->draw_width = ClientConfig::getProjWidth();
	this->draw_height = ClientConfig::getProjHeight();

	std::vector<std::vector<int>> normal_sprites = ClientConfig::getNormalProjectileSprites();
    for (int i = 0; i < normal_sprites.size(); i++) {
		this->sprites[Normal].push_back(RectangularSprite(normal_sprites[i]));
	}
	std::vector<std::vector<int>> bluebullet_sprites = ClientConfig::getBlueBulletSprites();    
	for (int i = 0; i < bluebullet_sprites.size(); i++) {
		this->sprites[BlueBullet].push_back(RectangularSprite(bluebullet_sprites[i]));
	} 
	std::vector<std::vector<int>> violetbullet_sprites = ClientConfig::getVioletBulletSprites(); 
    for (int i = 0; i < violetbullet_sprites.size(); i++) {
		this->sprites[VioletBullet].push_back(RectangularSprite(violetbullet_sprites[i]));
	}
	std::vector<std::vector<int>> redbomb_sprites = ClientConfig::getRedBombSprites();
	for (int i = 0; i < redbomb_sprites.size(); i++) {
		this->sprites[RedBomb].push_back(RectangularSprite(redbomb_sprites[i]));
	} 
	std::vector<std::vector<int>> violetbomb_sprites = ClientConfig::getVioletBombSprites();
	for (int i = 0; i < violetbomb_sprites.size(); i++) {
		this->sprites[VioletBomb].push_back(RectangularSprite(violetbomb_sprites[i]));
	}
}

std::list<RectangularSprite>::iterator Projectile::img_coords(uint32_t bulletId) {
	//Modificar que se pueda cambiar de bala
	std::list<RectangularSprite>::iterator it = this->sprites[Normal].begin();
	for (int i = 0; i != this->counts[bulletId]; i++) {
		++it;
		if (it == this->sprites[Normal].end()) {
			it = this->sprites[Normal].begin();
		}
		
	}
	this->counts[bulletId]++;
	return it;

}
void Projectile::draw_projectile(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile, std::vector<BulletDTO>& bullets) {
	int proj_pixel_x;
	int proj_pixel_w;
	int proj_pixel_y;
	int proj_pixel_h;		

	for (auto b : bullets) {
		if (!this->init) {
			this->counts[b.getBulletId()] = 0;
		}
		if (this->counts[b.getBulletId()] == 0) {
			proj_pixel_x = this->x_fire;
			proj_pixel_w = this->width_fire;
			proj_pixel_y = this->y_fire;
			proj_pixel_h = this->height_fire;
			this->counts[b.getBulletId()]++;
		} else {
			std::list<RectangularSprite>::iterator it2 = img_coords(b.getBulletId()); 
			proj_pixel_x = it2->getX();
			proj_pixel_w = it2->getWidth();	
			proj_pixel_y = it2->getY();
			proj_pixel_h = it2->getHeight();	
		}	
		double angle = 180.0;
		if (this->type == RedBomb || this->type == VioletBomb) {
			angle = 0.0;
		}
		renderer.Copy(projectile, SDL2pp::Rect(proj_pixel_x, proj_pixel_y, proj_pixel_w, proj_pixel_h), SDL2pp::Rect(b.getX(), b.getY(), this->draw_width, this->draw_height), angle, SDL2pp::NullOpt);
	
	}
	this->init = true;
	/*
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
	*/
}



