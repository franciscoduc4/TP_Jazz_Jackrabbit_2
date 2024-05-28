#ifndef ENEMYWEAPON
#define ENEMYWEAPON

#include "../sprite.h"

#include <SDL2pp/SDL2pp.hh>
#include <list>


class EnemyWeapon {
	std::list<Sprite> sprites;
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
	
	std::list<Sprite>::iterator weapon_coords();

	bool draw_weapon(SDL2pp::Renderer& renderer, SDL2pp::Texture& weapon);
};
#endif 
