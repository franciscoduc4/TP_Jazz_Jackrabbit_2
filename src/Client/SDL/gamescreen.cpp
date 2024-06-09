#include "gamescreen.h"
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include "../../Common/sprite.h"
#include "projectile.h"

#include "../../Common/Config/ClientConfig.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/player.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/item.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/tile.h"


//GameScreen::GameScreen(int character):
//        pj(character), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0) {}

GameScreen::GameScreen(Client& player): client(player), pj(1), points(0), level(0)/*, config(ClientConfig::getInstance())*/ {

}


void GameScreen::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    //SDL2pp::SDLTTF ttf;

    int window_width = 800;
    int window_height = 500;

    SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
                          window_height, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    //TEXTURAS NIVEL
    SDL_Surface* bg_surf = IMG_Load(this->level.getLevelPath(TileType::BACKGROUND).c_str()/* "../assets/scenes/BeachWorld/background.png" */);
    SDL2pp::Surface backgroundSurface(bg_surf);
    SDL2pp::Texture background(renderer, backgroundSurface);

    SDL_Surface* sandFloor_surf = IMG_Load(this->level.getLevelPath(TileType::FLOOR).c_str()/* "../assets/scenes/BeachWorld/fullFloor.png" */);
    SDL2pp::Surface sandFloorSurface(sandFloor_surf);
    sandFloorSurface.SetColorKey(true, SDL_MapRGB(sandFloorSurface.Get()->format, 87, 0, 203));
    SDL2pp::Texture sandFloor(renderer, sandFloorSurface);
    
    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> tiles_textures = this->level.getTilesTextures(renderer);

    //TEXTURAS PERSONAJES
    SDL_Surface* jazz_surf = IMG_Load(this->pj.getPath(CharacterType::JAZZ).c_str());
    SDL2pp::Surface jazzSurface(jazz_surf);
    jazzSurface.SetColorKey(true, SDL_MapRGB(jazzSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture jazz_sprite(renderer, jazzSurface);

    SDL_Surface* lori_surf = IMG_Load(this->pj.getPath(CharacterType::LORI).c_str());
    SDL2pp::Surface loriSurface(lori_surf);
    loriSurface.SetColorKey(true, SDL_MapRGB(loriSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture lori_sprite(renderer, loriSurface);

    SDL_Surface* spaz_surf = IMG_Load(this->pj.getPath(CharacterType::SPAZ).c_str());
    SDL2pp::Surface spazSurface(spaz_surf);
    spazSurface.SetColorKey(true, SDL_MapRGB(spazSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture spaz_sprite(renderer, spazSurface);

    std::map<CharacterType, SDL2pp::Texture*> pjs_textures;
    pjs_textures[CharacterType::JAZZ] = &jazz_sprite;
    pjs_textures[CharacterType::LORI] = &lori_sprite;
    pjs_textures[CharacterType::SPAZ] = &spaz_sprite;


    //TEXTURA ENEMIGOS
	SDL_Surface* enemy_surf = IMG_Load(this->enemies.getPath(EnemyType::WALKING_ENEMY).c_str());//IMG_Load(this->config->getTurtleFile().c_str());
    SDL2pp::Surface enemySurface(enemy_surf);
    enemySurface.SetColorKey(true, SDL_MapRGB(enemySurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture enemy(renderer, enemySurface);
	/*
	SDL_Surface* turtle_surf = IMG_Load(this->turtle.getPath().c_str());//IMG_Load(this->config->getTurtleFile().c_str());
    SDL2pp::Surface turtleSurface(turtle_surf);
    turtleSurface.SetColorKey(true, SDL_MapRGB(turtleSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture turtle_enemy(renderer, turtleSurface);
	
	SDL_Surface* sch_surf = IMG_Load(this->schartz_guard.getPath().c_str());
    SDL2pp::Surface schSurface(sch_surf);
    schSurface.SetColorKey(true, SDL_MapRGB(schSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture schartzenguard(renderer, schSurface);

    SDL_Surface* yellow_surf = IMG_Load(this->yellowM.getPath().c_str());
    SDL2pp::Surface yellowSurface(yellow_surf);
    yellowSurface.SetColorKey(true, SDL_MapRGB(yellowSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture yellowMonster(renderer, yellowSurface);
	*/
    //TEXTURAS PROJECTILES
    SDL_Surface* projectile_surf = IMG_Load("../assets/Miscellaneous/SFX.png");
    SDL2pp::Surface projectileSurface(projectile_surf);
    projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture projectile(renderer, projectileSurface);

    //TEXTURAS ITEMS
    SDL_Surface* items_surf = IMG_Load("../assets/Miscellaneous/Items&Objects.png");
    SDL2pp::Surface itemsSurface(items_surf);
    itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture items(renderer, itemsSurface);

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

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        {
		                    Command move = Command::MOVE;
		                    std::vector<uint8_t> par{static_cast<uint8_t>(Direction::RIGHT)};
		                    this->client.sendMsg(move, par);
		                    break;
                    	}
                    case SDLK_LEFT:
		                {    
		             		Command move = Command::MOVE;
		                    std::vector<uint8_t> elements{static_cast<uint8_t>(Direction::LEFT)};
		                    this->client.sendMsg(move, elements);
		                    break;
                    	}

                  	case SDLK_LSHIFT:
                        if (is_walking) {
                            speed_run = 3;
                            is_running = true;
                        }
                        break;
                    case SDLK_UP:
                        dir_y = -10;
                        break;
                    case SDLK_DOWN:
                        dir_y = 10;
                        break;
                    case SDLK_m:
                    	{
		                    //is_shooting = true;
		                    Command shoot = Command::SHOOT;
		                    std::vector<uint8_t> elements;
		                    this->client.sendMsg(shoot, elements);
		                    break;
		               	}
                    case SDLK_SPACE:
                        is_jumping = true;
                        break;
                    case SDLK_d:
                        is_dashing = true;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                        is_walking = false;
                        count_walk = 0;
                        dir_x = 0;
                        break;
                    case SDLK_LSHIFT:
                        is_running = false;
                        count_run = 0;
                        speed_run = 1;
                        break;
                    case SDLK_UP:
                    case SDLK_DOWN:
                        dir_y = 0;
                        break;
                }
            }
        }
		
		renderer.Clear();

        std::unique_ptr<DTO> serverMsg = this->client.getServerMsg();
        auto derived_ptr = static_cast<GameDTO*>(serverMsg.release());        
        std::unique_ptr<GameDTO> snapshot = std::unique_ptr<GameDTO>(derived_ptr);

        std::vector<PlayerDTO> players = snapshot->getPlayers();


        std::vector<int> dir_screen = this->level.draw_background(window, renderer, background, players[0]);
        this->level.draw_floor(window, renderer, sandFloor, players[0].getSpeed());
        x_screen = dir_screen[0];
        y_screen = dir_screen[1];
        
       	this->pj.draw_players(window, renderer, pjs_textures, players, x_screen, y_screen);
        
        std::vector<EnemyDTO> enemiesSnapshot = snapshot->getEnemies();
      	this->enemies.draw_enemy(window, renderer, enemy, enemiesSnapshot, players[0], x_screen, y_screen);
        
        std::vector<BulletDTO> bullets = snapshot->getBullets();
        
        std::vector<ItemDTO> itemsSnapshot = snapshot->getItems();
        this->points.draw_points(renderer, items, itemsSnapshot, players[0], x_screen, y_screen); 
        
        std::vector<WeaponDTO> weapons = snapshot->getWeapons();
        
        std::vector<TileDTO> tiles = snapshot->getTiles(); 
        this->level.draw_tiles(window, renderer, tiles_textures, tiles);
        
        x_screen = 0;
        y_screen = 0;
        
        renderer.Present();

        SDL_Delay(70);
    }

    return;
}




