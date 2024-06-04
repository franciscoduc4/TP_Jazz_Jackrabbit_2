#include "projectile.h"
#include "../../Common/sprite.h"

#include <SDL2pp/SDL2pp.hh>

#include <string>
#include <map>
#include <list>

class Player {
	std::string image_path;
	std::map<int, std::list<RectangularSprite>> sprites;
	std::list<Projectile> projectiles;
	
	
public:
	Player(int character);

	std::string getPath();
	
	std::list<RectangularSprite>::iterator img_coords(int mov_type, int num_mov);
	
	void shoot(int x, int y, int flip);
	
	void draw_projectiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile);
	
};
