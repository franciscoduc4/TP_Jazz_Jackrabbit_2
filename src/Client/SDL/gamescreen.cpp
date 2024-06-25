#include "gamescreen.h"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Music.hh>

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

#include <ctime>
#include <chrono>
#include "../../Common/printer.h"

GameScreen::GameScreen(GameController& controller, uint8_t playerId):
        controller(controller),
        mainPlayerId(playerId),
        level(0),
        proj(0),
        soundControl(0) {}
 
GameScreen::GameScreen(GameController& controller, uint8_t playerId, uint8_t mapId):
        controller(controller), mainPlayerId(playerId), level(mapId), proj(0), soundControl(mapId) {}

std::unique_ptr<PlayerDTO> GameScreen::searchMainPlayer(std::vector<PlayerDTO>& players) {
    int i = 0;

    while (i < players.size()) {
        if (players[i].getPlayerId() == this->mainPlayerId) {
            return std::make_unique<PlayerDTO>(players[i]);
        }
        i++;
    }
    if (i == 0) {
        return nullptr;
    }
    return std::make_unique<PlayerDTO>(players[i - 1]);
}

std::map<uint8_t, int> GameScreen::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    int window_width = 800;
    int window_height = 500;

    SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
                          window_height, SDL_WINDOW_RESIZABLE);

    std::cout << "[GAME SCREEN] Window created" << std::endl;

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::cout << "[GAME SCREEN] Renderer created" << std::endl;
      
    std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>> tiles_textures =
            this->level.getTilesTextures(renderer);
    std::cout << "[GAME SCREEN] Level textures created" << std::endl;

    std::map<CharacterType, std::unique_ptr<SDL2pp::Texture>> pjs_textures = this->pj.getPlayersTextures(renderer);
    std::cout << "[GAME SCREEN] Players sprites created" << std::endl;

    std::map<EnemyType, std::unique_ptr<SDL2pp::Texture>> enemies_textures = this->enemies.getEnemiesTextures(renderer);
    std::cout << "[GAME SCREEN] Enemies sprites created" << std::endl;

    std::unique_ptr<SDL2pp::Texture> projectile = this->proj.getProjectilesTextures(renderer);
    std::cout << "[GAME SCREEN] Projectile sprites created" << std::endl;

    std::unique_ptr<SDL2pp::Texture> items = this->points.getItemsTextures(renderer);
    std::cout << "[GAME SCREEN] Items sprites created" << std::endl;

    std::unique_ptr<SDL2pp::Texture> font = this->stats.getFontTextures(renderer); 
    std::cout << "[GAME SCREEN] Font sprites created" << std::endl;

    this->soundControl.play_backsound(); //EMPIEZA LA MUSICA DE FONDO
    
    
    int x_screen = 0;
    int y_screen = 0; 

    int pj_direction = 0;
    int speed = 0;   

    std::cout << "Textures created" << std::endl;

    const int frameDelay = 1000 / 30;
    Uint32 frameStart;
    int frameTime;

    std::time_t game_time = ClientConfig::getGameTime(); 
    std::time_t start = std::time({});

    std::map<uint8_t, int> scores;
    while (true) {
        SDL_Event event;
        std::cout << "[GAME SCREEN] Waiting for event" << std::endl;
        while (SDL_PollEvent(&event)) {
            frameStart = SDL_GetTicks();

            if (event.type == SDL_QUIT) {
                std::cout << "[GAME SCREEN] SDL_QUIT event received, exiting run loop" << std::endl;
                this->soundControl.free_musics();
                Mix_CloseAudio();
                return scores;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        {
		                    Command move = Command::MOVE;
		                    std::vector<uint8_t> par{static_cast<uint8_t>(Direction::RIGHT)};
		                    this->controller.sendMsg(this->mainPlayerId, move, par);
		                    pj_direction = 1;
                            speed = 2;
                            break;
                    	}
                    case SDLK_LEFT:
		                {
		             		Command move = Command::MOVE;
		                    std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::LEFT)};
		                    this->controller.sendMsg(this->mainPlayerId, move, elements);
                            pj_direction = -1;
                            speed = -2;
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
                        Command shoot = Command::SHOOT;
                        std::vector<uint8_t> elements;
                        this->controller.sendMsg(this->mainPlayerId, shoot, elements);
                        this->soundControl.play_sound_effect(SoundType::SHOOT);
                        break;
                    }
                    case SDLK_SPACE: {
                        Command move = Command::MOVE;
                        std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::UP)};
                        this->controller.sendMsg(this->mainPlayerId, move, elements);
                        pj_direction = -1;
                        speed = -2;
                        break;
                    }
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: case SDLK_LEFT: case SDLK_LSHIFT:
                        {
                            Command idle = Command::IDLE;
                            std::vector<uint8_t> elements;
                            this->controller.sendMsg(this->mainPlayerId, idle, elements);
                            speed = 0;
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
        std::vector<int> dir_screen = this->level.draw_background(window, renderer, tiles_textures, *mainPlayer, speed);
        x_screen = dir_screen[0];
        y_screen = dir_screen[1];
        //this->level.draw_floor(window, renderer, tiles_textures, *mainPlayer, speed, x_screen, y_screen);

        if (players.size() > 0) {
            this->pj.draw_players(window, renderer, pjs_textures, players, x_screen, y_screen, *mainPlayer, pj_direction);
        }

        std::vector<EnemyDTO> enemiesSnapshot = snapshot->getEnemies();
        std::cout << "Enemies size: " << enemiesSnapshot.size() << std::endl;
        if (enemiesSnapshot.size() > 0) {
            this->enemies.draw_enemy(window, renderer, enemies_textures, enemiesSnapshot, *mainPlayer, x_screen, y_screen);
        }
        
        std::vector<BulletDTO> bullets = snapshot->getBullets();
        if (bullets.size() > 0) {
            this->proj.draw_projectile(window, renderer, projectile, bullets, *mainPlayer, x_screen, y_screen);
        }

        std::vector<ItemDTO> itemsSnapshot = snapshot->getItems();
        if (itemsSnapshot.size() >  0) {
            this->points.draw_points(window, renderer, items, itemsSnapshot, *mainPlayer, x_screen, y_screen);
        }

        std::vector<WeaponDTO> weapons = snapshot->getWeapons();

        std::vector<TileDTO> tiles = snapshot->getTiles(); 
        if (tiles.size() > 0) {
            this->level.draw_tiles(window, renderer, tiles_textures, tiles, *mainPlayer, x_screen, y_screen);
        }
        auto const now = std::chrono::high_resolution_clock::now();
        std::time_t final = std::chrono::system_clock::to_time_t(now) - start;
        
        this->stats.draw_interface(window, renderer, *pjs_textures[mainPlayer->getCharacterType()], items, font, players, *mainPlayer, 3, game_time - final);
        scores = this->stats.sort_score(players);

        if (game_time - final == 0) {
            SDL_Delay(1000);
            this->soundControl.free_musics();
            Mix_CloseAudio(); 
            final_screen(window, renderer, *tiles_textures[ObstacleType::BACKGROUND], font);
            return scores;
        }

        x_screen = 0;
        y_screen = 0;
        
        renderer.Present();
        std::cout << "[GAME SCREEN] Frame presented" << std::endl;

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        //SDL_Delay(70);
    }
    this->soundControl.free_musics();
    Mix_CloseAudio();
    return scores;

}

void GameScreen::final_screen(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, std::unique_ptr<SDL2pp::Texture>& font) {
    while (true) {
        SDL_Event event;
        std::cout << "[GAME SCREEN] Waiting for event" << std::endl;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        renderer.Clear();
        this->stats.draw_game_finished(window, renderer, background, font);

        renderer.Present();
    }

}
