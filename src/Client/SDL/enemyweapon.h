#ifndef ENEMYWEAPON
#define ENEMYWEAPON

#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"


class EnemyWeapon {
	std::list<RectangularSprite> sprites;
	int count;
	int x;
	int y;
	int width;
	int height;
	int speed;
	int flip;
	bool activated;
	
public:
	EnemyWeapon(int enemy_weapon);
	
	void activate(int x, int y, int flip);	
	
	std::list<RectangularSprite>::iterator weapon_coords();

	bool draw_weapon(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& weapon);
};
#endif 
