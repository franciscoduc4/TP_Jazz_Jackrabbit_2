#ifndef CLIENT_GAME_SCREEN_H_
#define CLIENT_GAME_SCREEN_H_

#include <string>
#include <memory>

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
#include "soundController.h"

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
    SoundController soundControl;

    GameController& controller;
    uint8_t mainPlayerId;

public:
    GameScreen(GameController& controller, uint8_t playerId);

    //GameScreen(GameController& controller, uint8_t playerId, CharacterType pjId, uint8_t mapId);

    std::unique_ptr<PlayerDTO> searchMainPlayer(std::vector<PlayerDTO>& players);

    void run();
};

#endif  // CLIENT_GAME_SCREEN_H_
