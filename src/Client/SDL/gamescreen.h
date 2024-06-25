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

    GameScreen(GameController& controller, uint8_t playerId, uint8_t mapId);

    std::unique_ptr<PlayerDTO> searchMainPlayer(std::vector<PlayerDTO>& players);

    std::map<uint8_t, int> run();

    void final_screen(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, std::unique_ptr<SDL2pp::Texture>& font);
};

#endif  // CLIENT_GAME_SCREEN_H_
