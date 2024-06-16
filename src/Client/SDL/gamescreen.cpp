#include "gamescreen.h"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "../../Common/Config/ClientConfig.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/item.h"
#include "../../Common/DTO/player.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/tile.h"
#include "../../Common/sprite.h"

#include "projectile.h"

GameScreen::GameScreen(GameController& controller, uint8_t playerId):
        controller(controller),
        mainPlayerId(playerId),
        pj(1),
        level(0),
        proj(0) {}


std::unique_ptr<PlayerDTO> GameScreen::searchMainPlayer(std::vector<PlayerDTO>& players) {
    for (auto& player : players) {
        if (player.getPlayerId() == this->mainPlayerId) {
            return std::make_unique<PlayerDTO>(player);
        }
    }
    return nullptr;
}

void GameScreen::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    int window_width = 800;
    int window_height = 500;

    SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
                          window_height, SDL_WINDOW_RESIZABLE);

    std::cout << "[GAME SCREEN] Window created" << std::endl;

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::cout << "[GAME SCREEN] Renderer created" << std::endl;

    // TEXTURAS NIVEL
    SDL_Surface* bg_surf = IMG_Load(this->level.getLevelPath(TileType::BACKGROUND).c_str());
    if (!bg_surf) {
        std::cerr << "[GAME SCREEN] Error loading background surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface backgroundSurface(bg_surf);
    SDL2pp::Texture background(renderer, backgroundSurface);

    std::cout << "[GAME SCREEN] Background created" << std::endl;

    SDL_Surface* sandFloor_surf = IMG_Load(this->level.getLevelPath(TileType::FLOOR).c_str());
    if (!sandFloor_surf) {
        std::cerr << "[GAME SCREEN] Error loading floor surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface sandFloorSurface(sandFloor_surf);
    sandFloorSurface.SetColorKey(true, SDL_MapRGB(sandFloorSurface.Get()->format, 87, 0, 203));
    SDL2pp::Texture sandFloor(renderer, sandFloorSurface);

    std::cout << "[GAME SCREEN] Floor created" << std::endl;

    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> tiles_textures = this->level.getTilesTextures(renderer);

    // TEXTURAS PERSONAJES
    std::tuple<int, int, int> pjsColorKey = ClientConfig::getJazzColourKey();
    SDL_Surface* jazz_surf = IMG_Load(this->pj.getPath(CharacterType::JAZZ).c_str());
    if (!jazz_surf) {
        std::cerr << "[GAME SCREEN] Error loading Jazz surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface jazzSurface(jazz_surf);
    jazzSurface.SetColorKey(true, SDL_MapRGB(jazzSurface.Get()->format, std::get<0>(pjsColorKey),
                                             std::get<1>(pjsColorKey), std::get<2>(pjsColorKey)));
    SDL2pp::Texture jazz_sprite(renderer, jazzSurface);

    SDL_Surface* lori_surf = IMG_Load(this->pj.getPath(CharacterType::LORI).c_str());
    if (!lori_surf) {
        std::cerr << "[GAME SCREEN] Error loading Lori surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface loriSurface(lori_surf);
    loriSurface.SetColorKey(true, SDL_MapRGB(loriSurface.Get()->format, std::get<0>(pjsColorKey),
                                             std::get<1>(pjsColorKey), std::get<2>(pjsColorKey)));
    SDL2pp::Texture lori_sprite(renderer, loriSurface);

    SDL_Surface* spaz_surf = IMG_Load(this->pj.getPath(CharacterType::SPAZ).c_str());
    if (!spaz_surf) {
        std::cerr << "[GAME SCREEN] Error loading Spaz surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface spazSurface(spaz_surf);
    spazSurface.SetColorKey(true, SDL_MapRGB(spazSurface.Get()->format, std::get<0>(pjsColorKey),
                                             std::get<1>(pjsColorKey), std::get<2>(pjsColorKey)));
    SDL2pp::Texture spaz_sprite(renderer, spazSurface);

    std::map<CharacterType, SDL2pp::Texture*> pjs_textures;
    pjs_textures[CharacterType::JAZZ] = &jazz_sprite;
    pjs_textures[CharacterType::LORI] = &lori_sprite;
    pjs_textures[CharacterType::SPAZ] = &spaz_sprite;

    std::cout << "[GAME SCREEN] Players created" << std::endl;

    // TEXTURA ENEMIGOS
    SDL_Surface* enemy_surf = IMG_Load(this->enemies.getPath(EnemyType::TURTLE).c_str());
    if (!enemy_surf) {
        std::cerr << "[GAME SCREEN] Error loading enemy surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface enemySurface(enemy_surf);
    enemySurface.SetColorKey(true, SDL_MapRGB(enemySurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture enemy(renderer, enemySurface);

    // TEXTURAS PROJECTILES
    SDL_Surface* projectile_surf = IMG_Load("../assets/Miscellaneous/SFX.png");
    if (!projectile_surf) {
        std::cerr << "[GAME SCREEN] Error loading projectile surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface projectileSurface(projectile_surf);
    projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture projectile(renderer, projectileSurface);

    // TEXTURAS ITEMS
    SDL_Surface* items_surf = IMG_Load("../assets/Miscellaneous/Items&Objects.png");
    if (!items_surf) {
        std::cerr << "[GAME SCREEN] Error loading items surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface itemsSurface(items_surf);
    itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture items(renderer, itemsSurface);

    // TEXTURAS FONT
    std::tuple<int, int, int> fontColorKey = ClientConfig::getInterfaceFontColourKey();
    SDL_Surface* font_surf = IMG_Load(this->stats.getFontPath().c_str());
    if (!font_surf) {
        std::cerr << "[GAME SCREEN] Error loading font surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface fontSurface(font_surf);
    fontSurface.SetColorKey(true, SDL_MapRGB(fontSurface.Get()->format, std::get<0>(fontColorKey),
                                             std::get<1>(fontColorKey), std::get<2>(fontColorKey)));
    SDL2pp::Texture font(renderer, fontSurface);

    int walk_mov = 0;
    int count_walk = 0;

    int shoot_mov = 1;
    int count_shoot = 0;

    int run_mov = 2;
    int count_run = 0;

    int jump_mov = 3;
    int count_jump = 0;

    int dash_mov = 4;
    int count_dash = 0;
    int dash_timer = 0;

    bool is_walking = false;
    bool is_running = false;
    bool is_shooting = false;
    bool is_jumping = false;
    bool is_dashing = false;

    int dir_x = 0;
    int dir_y = 0;
    int speed_run = 1;

    int pos_x = 0;
    int pos_y = 0;

    int flip = 0;

    int x_screen = 0;
    int y_screen = 0;

    std::cout << "Textures created" << std::endl;

    while (true) {
        SDL_Event event;
        std::cout << "[GAME SCREEN] Waiting for event" << std::endl;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                std::cout << "[GAME SCREEN] SDL_QUIT event received, exiting run loop" << std::endl;
                return;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: {
                        Command move = Command::MOVE;
                        std::vector<uint8_t> par{static_cast<uint8_t>(Direction::RIGHT)};
                        this->controller.sendMsg(this->mainPlayerId, move, par);
                        break;
                    }
                    case SDLK_LEFT: {
                        Command move = Command::MOVE;
                        std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::LEFT)};
                        this->controller.sendMsg(this->mainPlayerId, move, elements);
                        break;
                    }

                    case SDLK_LSHIFT: {
                        /*
                        Command run = Command::RUN;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(this->mainPlayerId, move, elements);
                        break;
                        */
                    }
                    case SDLK_m: {
                        // is_shooting = true;
                        Command shoot = Command::SHOOT;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(this->mainPlayerId, shoot, elements);
                        break;
                    }

                    case SDLK_SPACE: {
                        Command move = Command::MOVE;
                        std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::UP)};
                        this->controller.sendMsg(this->mainPlayerId, move, elements);
                        break;
                    }
                    case SDLK_d: {
                        /*
                        Command dash = Command::DASH;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(this->mainPlayerId, dash, elements);
                        break;
                        */
                    }
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_LSHIFT: {
                        Command idle = Command::IDLE;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(this->mainPlayerId, idle, elements);
                        break;
                    }
                }
            }
        }

        std::cout << "[GAME SCREEN] Event handled" << std::endl;
        renderer.Clear();

        std::unique_ptr<DTO> serverMsg = this->controller.getServerMsg();

        if (!serverMsg) {
            std::cerr << "[GAME SCREEN] No message received from server." << std::endl;
            SDL_Delay(100);
            continue;
        }
        std::cout << "[GAME SCREEN] Received message from server" << std::endl;

        auto derived_ptr = static_cast<GameDTO*>(serverMsg.release());
        if (!derived_ptr) {
            std::cerr << "[GAME SCREEN] Failed to cast to GameDTO." << std::endl;
            SDL_Delay(100);
            continue;
        }
        std::unique_ptr<GameDTO> snapshot = std::unique_ptr<GameDTO>(derived_ptr);
        std::cout << "[GAME SCREEN] Snapshot created" << std::endl;

        std::vector<PlayerDTO> players = snapshot->getPlayers();
        if (players.empty()) {
            std::cerr << "[GAME SCREEN] No players found in snapshot." << std::endl;
            SDL_Delay(100);
            continue;
        }
        std::unique_ptr<PlayerDTO> mainPlayer = searchMainPlayer(players);
        if (!mainPlayer) {
            continue;
        }
        std::vector<int> dir_screen = this->level.draw_background(window, renderer, background,
                                                                  *mainPlayer /*players[0]*/);
        this->level.draw_floor(window, renderer, sandFloor,
                               mainPlayer->getSpeed() /*players[0].getSpeed()*/);
        x_screen = dir_screen[0];
        y_screen = dir_screen[1];

        if (players.size() > 0) {
            this->pj.draw_players(window, renderer, pjs_textures, players, x_screen, y_screen,
                                  this->mainPlayerId);
        }

        std::vector<EnemyDTO> enemiesSnapshot = snapshot->getEnemies();
        if (enemiesSnapshot.size() > 0) {
            this->enemies.draw_enemy(window, renderer, enemy, enemiesSnapshot,
                                     *mainPlayer /*players[0]*/, x_screen, y_screen);
        }
        std::cout << "[GAME SCREEN] Enemies drawn" << std::endl;

        std::vector<BulletDTO> bullets = snapshot->getBullets();
        if (bullets.size() > 0) {
            this->proj.draw_projectile(window, renderer, projectile, bullets);
        }

        std::vector<ItemDTO> itemsSnapshot = snapshot->getItems();
        if (itemsSnapshot.size() > 0) {
            this->points.draw_points(renderer, items, itemsSnapshot, *mainPlayer /*players[0]*/,
                                     x_screen, y_screen);
        }

        std::vector<WeaponDTO> weapons = snapshot->getWeapons();

        std::vector<TileDTO> tiles = snapshot->getTiles();
        if (tiles.size() > 0) {
            this->level.draw_tiles(window, renderer, tiles_textures, tiles);
        }

        this->stats.draw_interface(
                window, renderer, *pjs_textures[mainPlayer->getType() /*players[0].getType()*/],
                mainPlayer->getType(), font, 1000 /*getPoints()*/, 3 /*getLives()*/);

        x_screen = 0;
        y_screen = 0;

        renderer.Present();
        std::cout << "[GAME SCREEN] Frame presented" << std::endl;

        SDL_Delay(70);
    }
}
