#include "projectile.h"

enum projectile_type { Normal };

Projectile::Projectile(int p_type, int pos_x, int pos_y, int flip): x(pos_x), y(pos_y), flip(flip) {
	this->type = p_type;
	switch (p_type) {
		case Normal:
			this->y_src = 36;
			this->heights = 7;
			this->widths[44] = 13;
			this->widths[58] = 13;
			this->widths[73] = 13;	
	}	

}

void Projectile::setPos(int x, int y) {
	this->x = x; 
	this->y = y;
}

std::vector<int> Projectile::getPos() {
	std::vector<int> vector;
	vector.push_back(this->x);
	vector.push_back(this->y);
	return vector;
}

int Projectile::getYsrc() {
	return this->y_src;
}

std::map<int, int>::iterator Projectile::widthSrc() {
	std::map<int, int>::iterator it = this->widths.begin();
	for (int i = 0; i != this->count; i++) {
		++it;
		if (it == this->widths.end()) {
			it = this->widths.begin();
		}
	}
	this->count++;
	return it;
}

int Projectile::heightSrc() {
	return this->heights;
}

int Projectile::getDir() {
	return this->flip;
}


bool Projectile::draw_projectile(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile) {
	std::map<int, int>::iterator it2 = widthSrc(); 
	int proj_pixel_x = it2->first;
	int proj_pixel_w = it2->second;		
		
	int proj_speed = 20;
	if (this->flip == 1) {
		proj_speed = -20;
	}
		
	renderer.Copy(projectile, SDL2pp::Rect(proj_pixel_x, this->y_src, proj_pixel_w, this->heights), SDL2pp::Rect(this->x, this->y, 20, 10), 180.0, SDL2pp::NullOpt, this->flip);
		
	this->x += proj_speed;
		
	if (this->x < 0 || this->x > 800 || this->y < 0 || this->y > 500) {
		return false;
	}
	return true;
}



