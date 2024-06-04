#include <string>
#include "player.h"
#include "enemy.h"
#include "points.h"

#include "../../Common/queue.h"
#include "../../Common/DTO/game.h"
#include "../../Client/client.h"

class GameScreen {
	Player pj;
	Enemy turtle;
	Enemy schartz_guard;
	Enemy yellowM;
	Points points;
	
	
	/*
	Client& client;
	bool state;
	*/
public:
	
	GameScreen(int character, Queue<GameDTO>& cola);
	
	//explicit GameScreen(Client& player);
	
	void run();
	
};
