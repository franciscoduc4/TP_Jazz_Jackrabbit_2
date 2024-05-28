#include <string>
#include "player.h"
#include "enemy.h"
#include "points.h"

class GameScreen {
	Player pj;
	Enemy turtle;
	Enemy schartz_guard;
	Enemy yellowM;
	Points points;

public:
	GameScreen(int character, std::string map);
	
	void run();
	
};
