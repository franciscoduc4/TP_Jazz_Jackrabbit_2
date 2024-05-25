#include "projectile.h"

#include <SDL2pp/SDL2pp.hh>

#include <string>
#include <map>
#include <list>

class Player {
	std::string image_path;
	std::map<int, int> y_sprites; 
	std::map<int, int> heights;
	std::map<int, std::map<int, int>> widths;
	std::list<Projectile> projectiles;
	
public:
	Player(int character);

	std::string getPath();
	
	int getYsrc(int mov_type);
	
	std::map<int, int>::iterator widthSrc(int mov_type, int num_mov);
	
	int heightSrc(int mov_type);
	
	void shoot(int x, int y, int flip);
	
	void draw_projectiles(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile);
};
