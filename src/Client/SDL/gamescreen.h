#ifndef CLIENT_GAME_SCREEN_H_
#define CLIENT_GAME_SCREEN_H_

#include <string>

#include "../../Client/client.h"
#include "../../Common/DTO/game.h"
#include "../../Common/queue.h"

#include "enemy.h"
#include "player.h"
#include "points.h"

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

    // explicit GameScreen(Client& player);

    void run();
};

#endif  // CLIENT_GAME_SCREEN_H_