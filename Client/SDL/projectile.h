#ifndef PROJECTILE
#define PROJECTILE

#include <SDL2pp/SDL2pp.hh>

#include <map>
#include <vector>

class Projectile {
	int type;
	int x;
	int y;
	int flip;
	int count;
	int y_src;
	int heights;
	std::map<int, int> widths;
	
	
	
public:
	Projectile(int p_type, int pos_x, int pos_y, int flip);

	std::vector<int> getPos();
	
	void setPos(int x, int y);
	
	int getYsrc();

	std::map<int, int>::iterator widthSrc();
	
	int heightSrc();
	
	int getDir();
	
	bool draw_projectile(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile);
};
#endif
