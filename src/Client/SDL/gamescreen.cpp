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

GameScreen::GameScreen(GameController& controller):
        controller(controller), pj(1), points(0), level(0), stats(CharacterType::JAZZ) {}

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
        std::cerr << "[GAME SCREEN] Error loading background surface: " << IMG_GetError()
                  << std::endl;
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

    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> tiles_textures =
            this->level.getTilesTextures(renderer);

    // TEXTURAS PERSONAJES
    SDL_Surface* jazz_surf = IMG_Load(this->pj.getPath(CharacterType::JAZZ).c_str());
    if (!jazz_surf) {
        std::cerr << "[GAME SCREEN] Error loading Jazz surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface jazzSurface(jazz_surf);
    jazzSurface.SetColorKey(true, SDL_MapRGB(jazzSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture jazz_sprite(renderer, jazzSurface);

    SDL_Surface* lori_surf = IMG_Load(this->pj.getPath(CharacterType::LORI).c_str());
    if (!lori_surf) {
        std::cerr << "[GAME SCREEN] Error loading Lori surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface loriSurface(lori_surf);
    loriSurface.SetColorKey(true, SDL_MapRGB(loriSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture lori_sprite(renderer, loriSurface);

    SDL_Surface* spaz_surf = IMG_Load(this->pj.getPath(CharacterType::SPAZ).c_str());
    if (!spaz_surf) {
        std::cerr << "[GAME SCREEN] Error loading Spaz surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface spazSurface(spaz_surf);
    spazSurface.SetColorKey(true, SDL_MapRGB(spazSurface.Get()->format, 44, 102, 150));
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
        std::cerr << "[GAME SCREEN] Error loading projectile surface: " << IMG_GetError()
                  << std::endl;
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
    SDL_Surface* font_surf = IMG_Load(this->stats.getFontPath().c_str());
    if (!font_surf) {
        std::cerr << "[GAME SCREEN] Error loading font surface: " << IMG_GetError() << std::endl;
        return;
    }
    SDL2pp::Surface fontSurface(font_surf);
    fontSurface.SetColorKey(true, SDL_MapRGB(fontSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture font(renderer, fontSurface);

    std::cout << "[GAME SCREEN] Textures created" << std::endl;

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

    int32_t playerId = 0;
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
                        this->controller.sendMsg(playerId, move, par);
                        std::cout << "[GAME SCREEN] Sent MOVE command with direction RIGHT"
                                  << std::endl;
                        break;
                    }
                    case SDLK_LEFT: {
                        Command move = Command::MOVE;
                        std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::LEFT)};
                        this->controller.sendMsg(playerId, move, elements);
                        std::cout << "[GAME SCREEN] Sent MOVE command with direction LEFT"
                                  << std::endl;
                        break;
                    }

                    case SDLK_LSHIFT:
                        if (is_walking) {
                            speed_run = 3;
                            is_running = true;
                            std::cout << "[GAME SCREEN] Running mode activated" << std::endl;
                        }
                        break;
                    case SDLK_UP:
                        dir_y = -10;
                        std::cout << "[GAME SCREEN] Direction UP set" << std::endl;
                        break;
                    case SDLK_DOWN:
                        dir_y = 10;
                        std::cout << "[GAME SCREEN] Direction DOWN set" << std::endl;
                        break;
                    case SDLK_m: {
                        Command shoot = Command::SHOOT;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(playerId, shoot, elements);
                        std::cout << "[GAME SCREEN] Sent SHOOT command" << std::endl;
                        break;
                    }

                    case SDLK_SPACE:
                        is_jumping = true;
                        std::cout << "[GAME SCREEN] Jumping activated" << std::endl;
                        break;
                    case SDLK_d:
                        is_dashing = true;
                        std::cout << "[GAME SCREEN] Dashing activated" << std::endl;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                        is_walking = false;
                        count_walk = 0;
                        dir_x = 0;
                        std::cout << "[GAME SCREEN] Walking stopped" << std::endl;
                        break;
                    case SDLK_LSHIFT:
                        is_running = false;
                        count_run = 0;
                        speed_run = 1;
                        std::cout << "[GAME SCREEN] Running mode deactivated" << std::endl;
                        break;
                    case SDLK_UP:
                    case SDLK_DOWN:
                        dir_y = 0;
                        std::cout << "[GAME SCREEN] Vertical direction reset" << std::endl;
                        break;
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
        std::cout << "[GAME SCREEN] Players extracted from snapshot" << std::endl;

        std::vector<int> dir_screen =
                this->level.draw_background(window, renderer, background, players[0]);
        this->level.draw_floor(window, renderer, sandFloor, players[0].getSpeed());
        x_screen = dir_screen[0];
        y_screen = dir_screen[1];

        this->pj.draw_players(window, renderer, pjs_textures, players, x_screen, y_screen);

        std::vector<EnemyDTO> enemiesSnapshot = snapshot->getEnemies();
        this->enemies.draw_enemy(window, renderer, enemy, enemiesSnapshot, players[0], x_screen,
                                 y_screen);
        std::cout << "[GAME SCREEN] Enemies drawn" << std::endl;

        std::vector<BulletDTO> bullets = snapshot->getBullets();
        // Draw bullets here, if needed

        std::vector<ItemDTO> itemsSnapshot = snapshot->getItems();
        this->points.draw_points(renderer, items, itemsSnapshot, players[0], x_screen, y_screen);
        std::cout << "[GAME SCREEN] Items drawn" << std::endl;

        std::vector<WeaponDTO> weapons = snapshot->getWeapons();
        // Draw weapons here, if needed

        std::vector<TileDTO> tiles = snapshot->getTiles();
        this->level.draw_tiles(window, renderer, tiles_textures, tiles);
        std::cout << "[GAME SCREEN] Tiles drawn" << std::endl;

        this->stats.draw_interface(window, renderer, *pjs_textures[players[0].getType()], font,
                                   1000, 3);
        std::cout << "[GAME SCREEN] Interface drawn" << std::endl;

        x_screen = 0;
        y_screen = 0;

        renderer.Present();
        std::cout << "[GAME SCREEN] Frame presented" << std::endl;

        SDL_Delay(70);
    }
}
