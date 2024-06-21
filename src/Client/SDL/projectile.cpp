#include "projectile.h"
#include "../../Common/sprite.h"
#include "../Common/Config/ClientConfig.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

std::unique_ptr<SDL2pp::Texture> Projectile::getProjectilesTextures(SDL2pp::Renderer& renderer) {
	SDL_Surface* projectile_surf = IMG_Load("../assets/Miscellaneous/SFX.png");
    SDL2pp::Surface projectileSurface(projectile_surf);
    projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
	return std::make_unique<SDL2pp::Texture>(renderer, projectileSurface);
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
void Projectile::draw_projectile(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& projectile, std::vector<BulletDTO>& bullets, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
	int proj_pixel_x;
	int proj_pixel_w;
	int proj_pixel_y;
	int proj_pixel_h;		

	uint32_t x;
	uint32_t y;
	int distance_main_bullet_x = 0;
	int distance_main_bullet_y = 0;
	double angle = 180.0;
	std::list<RectangularSprite>::iterator it2;
	for (auto b : bullets) {
		uint8_t bulletId = b.getBulletId();
		auto it = this->counts.find(bulletId);
		if (it == this->counts.end()) {
			this->counts[bulletId] = 0;
		}
		if (this->counts[bulletId] == 0) {
			proj_pixel_x = this->x_fire;
			proj_pixel_w = this->width_fire;
			proj_pixel_y = this->y_fire;
			proj_pixel_h = this->height_fire;
			this->counts[bulletId]++;
		} else {
			it2 = img_coords(bulletId); 
			proj_pixel_x = it2->getX();
			proj_pixel_w = it2->getWidth();	
			proj_pixel_y = it2->getY();
			proj_pixel_h = it2->getHeight();	
		}	
		if (this->type == RedBomb || this->type == VioletBomb) {
			angle = 0.0;
		}
		x = b.getX();
		y = b.getY();

		if (dir_x_screen != 0) { 
            distance_main_bullet_x = x - player.getX();
            x = dir_x_screen + distance_main_bullet_x;
        }
        if (dir_y_screen != 0) {
            distance_main_bullet_y = y - player.getX();
            y = dir_y_screen + distance_main_bullet_y;
        }
		if (abs(distance_main_bullet_x) <= window.GetWidth() && abs(distance_main_bullet_y) <= window.GetHeight()) {
			renderer.Copy(*projectile, SDL2pp::Rect(proj_pixel_x, proj_pixel_y, proj_pixel_w, proj_pixel_h), SDL2pp::Rect(x, y, this->draw_width, this->draw_height), angle, SDL2pp::NullOpt);
		}
	}
}