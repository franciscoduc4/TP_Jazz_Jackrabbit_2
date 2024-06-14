#ifndef CLIENT_GAME_SCREEN_H_
#define CLIENT_GAME_SCREEN_H_

#include <string>

#include "../../Client/client.h"
#include "../../Common/DTO/game.h"
#include "../../Common/queue.h"
#include "../../Client/Controllers/GameController.h"

#include "../../Common/Config/ClientConfig.h"

#include "enemy.h"
#include "player.h"
#include "points.h"
#include "level.h"
#include "projectile.h"
#include "interface.h"

class GameScreen {
    Player pj;
    /*
    Enemy turtle;
    Enemy schartz_guard;
    Enemy yellowM;
    */
    Enemy enemies;
    Points points;
    Level level;
    Projectile proj;
    Interface stats;

    GameController& controller;
    uint32_t mainPlayerId;

public:
    GameScreen(GameController& controller, uint32_t playerId);

    PlayerDTO searchMainPlayer(std::vector<PlayerDTO>& players);

    void run();
};

#endif  // CLIENT_GAME_SCREEN_H_
