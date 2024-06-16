#ifndef CLIENT_GAME_SCREEN_H_
#define CLIENT_GAME_SCREEN_H_

#include <memory>
#include <string>

#include "../../Client/Controllers/GameController.h"
#include "../../Client/client.h"
#include "../../Common/Config/ClientConfig.h"
#include "../../Common/DTO/game.h"
#include "../../Common/queue.h"

#include "enemy.h"
#include "interface.h"
#include "level.h"
#include "player.h"
#include "points.h"
#include "projectile.h"

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
    uint8_t mainPlayerId;

    void sendMoveCommand(Direction dir);
    void sendShootCommand();
    void sendIdleCommand();

public:
    GameScreen(GameController& controller, uint8_t playerId);

    std::unique_ptr<PlayerDTO> searchMainPlayer(std::vector<PlayerDTO>& players);

    void run();
};

#endif  // CLIENT_GAME_SCREEN_H_
