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


//GameScreen::GameScreen(int character):
//        pj(character), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0) {}

GameScreen::GameScreen(Client& player): client(player), pj(0), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0)/*, config(ClientConfig::getInstance())*/ {

}


void GameScreen::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    //SDL2pp::SDLTTF ttf;

    int window_width = 800;
    int window_height = 500;

    SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
                          window_height, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* bg_surf = IMG_Load("../assets/Tilesets/BeachWorld-1.png");
    SDL2pp::Surface backgroundSurface(bg_surf);
    SDL2pp::Texture background(renderer, backgroundSurface);

    SDL_Surface* pj_surf = IMG_Load(this->pj.getPath().c_str());
    SDL2pp::Surface pjSurface(pj_surf);
    pjSurface.SetColorKey(true, SDL_MapRGB(pjSurface.Get()->format, 44, 102, 150));
    SDL2pp::Texture jazz_sprite(renderer, pjSurface);

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

    SDL_Surface* projectile_surf = IMG_Load("../assets/Miscellaneous/SFX.png");
    SDL2pp::Surface projectileSurface(projectile_surf);
    projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
    SDL2pp::Texture projectile(renderer, projectileSurface);

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

    std::list<RectangularSprite>::iterator it = this->pj.img_coords(walk_mov, count_walk);
    int pixel_x = it->getX();
    int pixel_y = it->getY();
    int pixel_width = it->getWidth();
    int pixel_height = it->getHeight();

    int flip = 0;

	int x_screen = 0;
	int y_screen = 0;
    int pixel_x_screen = 0;
    int pixel_y_screen = 0;
    int pixel_width_screen = 200;
    int pixel_height_screen = 200;

    int img_width = 318;
    int img_height = 2687;

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        {
		                    /*
		                    is_walking = true;
		                    dir_x = 5;
		                    flip = 0;
		                	*/
		                    Command move = Command::MOVE;
		                    std::vector<uint8_t> par{static_cast<uint8_t>(Direction::RIGHT)};
		                    this->client.sendMsg(move, par);
		                    break;
                    	}
                    case SDLK_LEFT:
		                {    
		                    /*
		                    is_walking = true;
		                    dir_x = -5;
		                    flip = 1;
		                    break;
		                	*/
                    		Command move = Command::MOVE;
		                    std::vector<uint8_t> par{static_cast<uint8_t>(Direction::LEFT)};
		                    this->client.sendMsg(move, par);
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
                        is_shooting = true;
                        break;
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

        renderer.Copy(background,
                      SDL2pp::Rect(pixel_x_screen, pixel_y_screen, pixel_width_screen,
                                   pixel_height_screen),
                      SDL2pp::Rect(0, 0, window_width, window_height));
        
        
        std::unique_ptr<DTO> serverMsg = this->client.getServerMsg();
		auto derived_ptr = static_cast<GameDTO*>(serverMsg.release());        
        std::unique_ptr<GameDTO> snapshot = std::unique_ptr<GameDTO>(derived_ptr);
   		
   		std::vector<PlayerDTO> players = snapshot->getPlayers();
       	this->pj.draw_players(window, renderer, jazz_sprite, players, 0);
        
        
        std::vector<EnemyDTO> enemies = snapshot->getEnemies();
      	
        
        std::vector<BulletDTO> bullets = snapshot->getBullets();
        
        std::vector<ItemDTO> items = snapshot->getItems();
        
        std::vector<WeaponDTO> weapons = snapshot->getWeapons();
        
        std::vector<TileDTO> tiles = snapshot->getTiles(); 


        renderer.Present();

        SDL_Delay(70);
    }

    return;
}




