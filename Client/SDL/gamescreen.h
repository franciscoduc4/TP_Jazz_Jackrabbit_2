#include <string>
#include "player.h"
#include "enemy.h"

class GameScreen {
	Player pj;
	Enemy turtle;
	Enemy schartz_guard;
	Enemy yellowM;

public:
	GameScreen(int character, std::string map);
	
	void run();
	
};
