#include "../sprite.h"
#include "enemyweapon.h"

#include <SDL2pp/SDL2pp.hh>

#include <map>
#include <string>
#include <list>

class Enemy {
	std::string path;	
	std::map<int, std::list<Sprite>> sprites;	
	EnemyWeapon weapon;
	int count;
	int pos_x;
	int pos_y;
	int draw_width;
	int draw_height;
	int flip;
	int speed;
	

public:
	Enemy(int enemy, int x, int y);
	
	std::string getPath();

	std::list<Sprite>::iterator enemy_img_coords(int mov_type, int num_mov);	
	
	void draw_enemy(SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy, int mov_type);
};
