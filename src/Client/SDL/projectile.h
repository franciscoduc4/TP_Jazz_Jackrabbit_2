#ifndef PROJECTILE
#define PROJECTILE

#include <SDL2pp/SDL2pp.hh>
#include "../../Common/sprite.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/player.h"

#include <map>
#include <list>
#include <vector>
#include <memory>

class Projectile {
	int type;
	int y_fire;
	int x_fire;
	int width_fire;
	int height_fire;
	int draw_width;
	int draw_height;

	std::map<int, std::list<RectangularSprite>> sprites;
	std::map<uint32_t, int> counts;
	bool init;
			
	
	
public:
	explicit Projectile(int p_type);

	std::unique_ptr<SDL2pp::Texture> getProjectilesTextures(SDL2pp::Renderer& renderer);

	std::list<RectangularSprite>::iterator img_coords(uint32_t bulletId);
	
	void draw_projectile(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& projectile, std::vector<BulletDTO>& bullets, PlayerDTO& player, int dir_x_screen, int dir_y_screen, int pos_x, int pos_y);
};
#endif
