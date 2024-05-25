#include "player.h"

#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <SDL2pp/SDL2pp.hh>

#include <iostream>

enum character_type { Jazz, Lori, Spaz };
enum type_mov { Walk, Shoot, Run, Jump };


Player::Player(int character) {
	switch (character) {
		case Jazz:
			this->image_path = "../assets/Characters/Jazz.png";
			this->y_sprites[Walk] = 790;
			this->y_sprites[Shoot] = 557;
			this->y_sprites[Run] = 853;
			this->y_sprites[Jump] = 1197;
			
			this->heights[Walk] = 46;
			this->heights[Shoot] = 57;
			this->heights[Run] = 39;
			this->heights[Jump] = 60;
			
			for (int i = 0; i < 8; i++) {
				this->widths[Walk][57 * i] = 57;
				this->widths[Run][67 * i] = 67;
			}
			this->widths[Shoot][0] = 47;
			this->widths[Shoot][51] = 45;
			this->widths[Shoot][101] = 36;
			this->widths[Shoot][143] = 37;
			this->widths[Shoot][185] = 36;
			this->widths[Shoot][226] = 39;
			this->widths[Shoot][265] = 54;
			this->widths[Jump][0] = 50;
			this->widths[Jump][53] = 36;
			this->widths[Jump][89] = 43;
			this->widths[Jump][132] = 46;
			this->widths[Jump][178] = 48;
			this->widths[Jump][226] = 52;			
			this->widths[Jump][278] = 51;
			this->widths[Jump][329] = 53;
			this->widths[Jump][383] = 45;
			this->widths[Jump][429] = 36;
			this->widths[Jump][465] = 35;
			this->widths[Jump][500] = 37;
			
			break;
		case Lori:
			this->image_path = "../assets/Characters/Lori.png";
			
			this->y_sprites[Walk] = 556;
			this->y_sprites[Shoot] = 341;
			this->y_sprites[Run] = 626;
			this->y_sprites[Jump] = 963;
			
			this->heights[Walk] = 51;
			this->heights[Shoot] = 56;
			this->heights[Run] = 42;
			this->heights[Jump] = 70;
			
			for (int i = 0; i < 8; i++) {
				this->widths[Walk][51 * i] = 51;
				this->widths[Run][55 * i] = 55;
			}
			this->widths[Shoot][0] = 48;
			this->widths[Shoot][50] = 43;
			this->widths[Shoot][100] = 38;
			this->widths[Shoot][140] = 37;
			this->widths[Shoot][180] = 40;
			this->widths[Shoot][220] = 40;
			this->widths[Jump][0] = 48;
			this->widths[Jump][50] = 45;	
			this->widths[Jump][98] = 44;
			this->widths[Jump][145] = 45;
			this->widths[Jump][190] = 45;
			this->widths[Jump][235] = 52;
			this->widths[Jump][288] = 52;
			this->widths[Jump][340] = 52;
			this->widths[Jump][392] = 53;
			this->widths[Jump][445] = 37;
			this->widths[Jump][485] = 40;
			this->widths[Jump][525] = 40;
			this->widths[Jump][565] = 40;
				
		
			break;
		case Spaz:
			this->image_path = "../assets/Characters/Spaz.png";
		
			this->y_sprites[Walk] = 747;
			this->y_sprites[Shoot] = 539;
			this->y_sprites[Run] = 807;
			this->y_sprites[Jump] = 1139;
			
			this->heights[Walk] = 45;
			this->heights[Shoot] = 48;
			this->heights[Run] = 40;
			this->heights[Jump] = 55;
			
			for (int i = 0; i < 8; i++) {
				this->widths[Walk][50 * i] = 50;
			}
			this->widths[Run][0] = 48;
			this->widths[Run][48] = 58;
			this->widths[Run][106] = 52;
			this->widths[Run][160] = 48;
			this->widths[Run][210] = 48;
			this->widths[Run][260] = 54;
			this->widths[Run][315] = 50;
			this->widths[Run][366] = 50;
			
			
			this->widths[Shoot][0] = 52;
			this->widths[Shoot][53] = 50;
			this->widths[Shoot][105] = 48;
			this->widths[Shoot][153] = 36;
			this->widths[Shoot][190] = 42;
			this->widths[Shoot][232] = 47;
			
			this->widths[Jump][0] = 44;
			this->widths[Jump][44] = 36;	
			this->widths[Jump][81] = 40;
			this->widths[Jump][122] = 42;
			this->widths[Jump][165] = 38;
			this->widths[Jump][205] = 40;
			this->widths[Jump][245] = 40;
			this->widths[Jump][287] = 43;
			this->widths[Jump][330] = 45;
			this->widths[Jump][378] = 34;
			this->widths[Jump][415] = 33;
			this->widths[Jump][450] = 34;
		
			break;
	}
}

std::string Player::getPath() {
	return this->image_path;
}

int Player::getYsrc(int mov_type) {
	return this->y_sprites[mov_type];
}

std::map<int, int>::iterator Player::widthSrc(int mov_type, int num_mov) {
	std::map<int, int>::iterator it = this->widths[mov_type].begin();
	for (int i = 0; i != num_mov; i++) {
		++it;
		if (it == this->widths[mov_type].end()) {
			it = this->widths[mov_type].begin();
		}
	}
	return it;
}

int Player::heightSrc(int mov_type) {
	return this->heights[mov_type];
}


void Player::shoot(int x, int y, int flip) {
	Projectile p(0, x, y, flip);
	this->projectiles.push_back(p);
}


void Player::draw_projectiles(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile) {
	std::list<Projectile>::iterator it = this->projectiles.begin();
	
	/*
	int proj_pixel_x;
	int proj_pixel_w;		
	int proj_pixel_y;
	int proj_pixel_h;
	std::vector<int> proj_pos;
	int proj_pos_x; 
	int proj_pos_y;
	int flip;
	*/
	
	while (it != this->projectiles.end()) {
		/*
		std::map<int, int>::iterator it2 = it->widthSrc(); 
		proj_pixel_x = it2->first;
		proj_pixel_w = it2->second;		
		proj_pixel_y = it->getYsrc();
		proj_pixel_h = it->heightSrc();
		proj_pos = it->getPos();
		proj_pos_x = proj_pos[0]; 
		proj_pos_y = proj_pos[1];
		flip = it->getDir();
		
		int proj_speed = 20;
		if (flip == 1) {
			proj_speed = -20;
		}
		
		renderer.Copy(projectile, SDL2pp::Rect(proj_pixel_x, proj_pixel_y, proj_pixel_w, proj_pixel_h), SDL2pp::Rect(proj_pos_x, proj_pos_y, 20, 10), 180.0, SDL2pp::NullOpt, flip);
		
		proj_pos_x += proj_speed;
		
		if (proj_pos_x < 0 || proj_pos_x > 800 || proj_pos_y < 0 || proj_pos_y > 500) {
			it = this->projectiles.erase(it);
		} else {			
			it->setPos(proj_pos_x, proj_pos_y);
			++it;			
		}
		*/
		if (!it->draw_projectile(renderer, projectile)) {
			it = this->projectiles.erase(it);
		} else {
			++it;
		}
		
	}

}

