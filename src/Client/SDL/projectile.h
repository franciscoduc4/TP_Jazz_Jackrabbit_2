#ifndef PROJECTILE
#define PROJECTILE

#include <SDL2pp/SDL2pp.hh>
#include "../../Common/sprite.h"

#include <map>
#include <list>
#include <vector>

class Projectile {
	int type;
	int x;
	int y;
	int flip;
	int count;
	int y_fire;
	int x_fire;
	int width_fire;
	int height_fire;
	
	std::list<RectangularSprite> sprites;
			
	
	
public:
	Projectile(int p_type, int pos_x, int pos_y, int flip);

	std::list<RectangularSprite>::iterator img_coords();
	
	bool draw_projectile(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile);
};
#endif
