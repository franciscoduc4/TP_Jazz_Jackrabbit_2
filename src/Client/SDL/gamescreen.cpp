#include "gamescreen.h"
#include "projectile.h"
#include "../Common/sprite.h"

#include "../Common/queue.h"
#include "../Common/DTO/game.h"
#include "../Common/DTO/player.h"
#include "../Common/DTO/enemy.h"
#include "../Common/Types/command.h"
#include "../Common/Types/direction.h"

#include "../Client/client.h"


#include <SDL2pp/SDL2pp.hh>

#include <iterator>
#include <map>
#include <vector>

#include <iostream>


GameScreen::GameScreen(int character, Queue<GameDTO>& cola): pj(character), colaDto(cola), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0), state(true) {}


//GameScreen::GameScreen(Client& player): client(player) {}

void GameScreen::run() {
	/*
	SDL2pp::SDL sdl(SDL_INIT_VIDEO);
	SDL2pp::SDLTTF ttf;
	
	int window_width= 800;
	int window_height = 500;
	
	SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);

	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		
	SDL2pp::Texture background(renderer, "../assets/Tilesets/BeachWorld-1.png"); //FONDO DE PRUEBA
 	
 	Player pj(0);
 	SDL2pp::Surface pjSurface(pj.getPath());
 	pjSurface.SetColorKey(true, SDL_MapRGB(pjSurface.Get()->format, 44, 102, 150));
 	SDL2pp::Texture jazz_sprite(renderer, pjSurface);	
	
	Enemy turtle(0, 0, 200);
	SDL2pp::Surface turtleSurface(turtle.getPath());
	turtleSurface.SetColorKey(true, SDL_MapRGB(turtleSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture turtle_enemy(renderer, turtleSurface);
	
	Points points(0);
	SDL2pp::Surface itemsSurface("../assets/Miscellaneous/Items&Objects.png");
	itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture items(renderer, itemsSurface);
	/*
	SDL2pp::Surface schSurface(this->schartz_guard.getPath());
	schSurface.SetColorKey(true, SDL_MapRGB(schSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture schartzenguard(renderer, schSurface);
	
	SDL2pp::Surface yellowSurface(this->yellowM.getPath());
	yellowSurface.SetColorKey(true, SDL_MapRGB(yellowSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture yellowMonster(renderer, yellowSurface);
	
	
	SDL2pp::Surface projectileSurface("../assets/Miscellaneous/SFX.png");
	projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture projectile(renderer, projectileSurface);
	
	
	SDL2pp::Surface itemsSurface("../assets/Miscellaneous/Items&Objects.png");
	itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture items(renderer, itemsSurface);
	
	
	bool gameFinished = false;
	
	int pixel_x_screen = 0;
	int pixel_y_screen = 0;
	int pixel_width_screen = 200;
	int pixel_height_screen = 200;
	
	
	int pos_x;
	int pos_y;
	
	int walk_mov = 0;
	int count_walk = 0;
	
	std::list<RectangularSprite>::iterator it = pj.img_coords(walk_mov, count_walk); 
	int pixel_x = it->getX();
	int pixel_y = it->getY();
	int pixel_width = it->getWidth();
	int pixel_height = it->getHeight();
	int flip = 0;
	
	while (!gameFinished) {
		std::cout << "PASA POR EL PRINCIPIO DEL LOOP\n";
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				this->state = false;
				std::cout << "TERMINO EL LOOP\n";
				return;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT: 
						std::vector<uint8_t> parameters(static_cast<uint8_t>(Direction::RIGHT));
						Command move = Command::MOVE;
						this->client.sendMsg(move, parameters);
						break;
				}
			}
		}
		renderer.Clear();

		renderer.Copy(background, SDL2pp::Rect(pixel_x_screen, pixel_y_screen, pixel_width_screen, pixel_height_screen), SDL2pp::Rect(0, 0, window_width, window_height));

		
		GameDTO snapshot = dynamic_cast<GameDTO>(this->client.getServerMsg());
		std::cout << "POPEO DE LA COLA\n";
		
		std::vector<PlayerDTO> players = snapshot.getPlayers();
		for (auto p: players) {
			pos_x = p.getX();
			pos_y = p.getY();
			
			SDL2pp::Rect player_rect = SDL2pp::Rect(pos_x, pos_y, 50, 80);
			renderer.Copy(jazz_sprite, SDL2pp::Rect(pixel_x, pixel_y, pixel_width, pixel_height), player_rect, 0.0, SDL2pp::NullOpt, flip);
		}			
		
		
		std::list<RectangularSprite>::iterator it2 = turtle.enemy_img_coords(walk_mov, count_walk); 
		int pixel_enemy_x = it2->getX();
		int pixel_enemy_y = it2->getY();
		int pixel_enemy_width = it2->getWidth();
		int pixel_enemy_height = it2->getHeight();

		std::vector<EnemyDTO> enemies = snapshot.getEnemies();
		for (auto e : enemies) {
			int enemy_pos_x = e.getX();
			int enemy_pos_y = e.getY();	

			renderer.Copy(turtle_enemy, SDL2pp::Rect(pixel_enemy_x, pixel_enemy_y, pixel_enemy_width, pixel_enemy_height), SDL2pp::Rect(enemy_pos_x, enemy_pos_y, 50, 50), 0.0, SDL2pp::NullOpt, flip);	
			
		}
	
		std::list<RectangularSprite>::iterator it3 = points.actual_sprite_coord(0); 
		int pixel_item_x = it3->getX();
		int pixel_item_y = it3->getY();
		int pixel_item_width = it3->getWidth();
		int pixel_item_height = it3->getHeight();
		std::vector<ItemDTO> itemsSnapshot = snapshot.getItems();
		for (auto item : itemsSnapshot) {
			int item_pos_x = item.getX();
			int item_pos_y = item.getY();	
			//int item_type = item.getType();
			renderer.Copy(items, SDL2pp::Rect(pixel_item_x, pixel_item_y, pixel_item_width, pixel_item_height), SDL2pp::Rect(item_pos_x, item_pos_y, 20, 20), 0.0, SDL2pp::NullOpt, flip);	
			
		}
		
		renderer.Present();
		
		SDL_Delay(70);
		/*
		std::vector<BulletDTO> bullets = snapshot.getBullets();
		std::vector<ItemDTO> items = snapshot.getItems();
		std::vector<WeaponDTO> weapons = snapshot.getWeapons();
		std::vector<TileDTO> tiles = snapshot.getTiles();
		*/
	}
	
	*/

	SDL2pp::SDL sdl(SDL_INIT_VIDEO);
	SDL2pp::SDLTTF ttf;
	
	int window_width= 800;
	int window_height = 500;
	
	SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);

	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		
	SDL2pp::Texture background(renderer, "../assets/Tilesets/BeachWorld-1.png"); //FONDO DE PRUEBA
 	
 	SDL2pp::Surface pjSurface(pj.getPath());
 	pjSurface.SetColorKey(true, SDL_MapRGB(pjSurface.Get()->format, 44, 102, 150));
 	SDL2pp::Texture jazz_sprite(renderer, pjSurface);	
	
	SDL2pp::Surface turtleSurface(turtle.getPath());
	turtleSurface.SetColorKey(true, SDL_MapRGB(turtleSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture turtle_enemy(renderer, turtleSurface);
	
	SDL2pp::Surface itemsSurface("../assets/Miscellaneous/Items&Objects.png");
	itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture items(renderer, itemsSurface);
	
	SDL2pp::Surface schSurface(this->schartz_guard.getPath());
	schSurface.SetColorKey(true, SDL_MapRGB(schSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture schartzenguard(renderer, schSurface);
	
	SDL2pp::Surface yellowSurface(this->yellowM.getPath());
	yellowSurface.SetColorKey(true, SDL_MapRGB(yellowSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture yellowMonster(renderer, yellowSurface);
	
	
	SDL2pp::Surface projectileSurface("../assets/Miscellaneous/SFX.png");
	projectileSurface.SetColorKey(true, SDL_MapRGB(projectileSurface.Get()->format, 0, 128, 255));
	SDL2pp::Texture projectile(renderer, projectileSurface);
	
	
	SDL2pp::Surface itemsSurface("../assets/Miscellaneous/Items&Objects.png");
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
						is_walking = true;
						dir_x = 5;
						flip = 0;					
						break;
					case SDLK_LEFT:
						is_walking = true;
						dir_x = -5;
						flip = 1;
						break;
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
					case SDLK_RIGHT: case SDLK_LEFT: 
						is_walking = false;
						count_walk = 0;
						dir_x = 0;
						break;
				 	case SDLK_LSHIFT:
				 		is_running = false;
						count_run = 0;
						speed_run = 1;
						break;
					case SDLK_UP: case SDLK_DOWN:
						dir_y = 0;
						break;
				}
			}
		} 
		
				
		
		int mov = walk_mov;
		int count = count_walk;
		if (is_running) {
			mov = run_mov;
		}
		
		if ((is_walking || is_running) && !is_shooting) {		
			if (is_running) {
				count = count_run;
			} else {
				count = count_walk;
			}
			if (is_running) {
				count_run++;
			} else {
				count_walk++;
			}
			
		}
		
		
		if (is_dashing) {
			if (count_dash == 17) {
				count_dash = 13;
				if (flip == 0) {
					dir_x = 20;
				} else {
					dir_x = -20;
				}
				dash_timer++;
			}
			mov = dash_mov;
			count = count_dash;
			count_dash++;
			if (dash_timer == 5) {
				is_dashing = false;
				count_dash = 0;
				dash_timer = 0;
				dir_x = 0;
				mov = walk_mov;
				count = count_walk;
			}
		}		
		
		if (is_shooting) {
			if (count_shoot == 2) {
				int proj_x = pos_x;
				if (flip == 0) {
					proj_x += 50;
				}
				int proj_y = pos_y + (50 / 2);
				this->pj.shoot(proj_x, proj_y, flip);
			}
		
			if (count_shoot == 7) {				
				count_shoot = 0;
				is_shooting = false; 
				mov = walk_mov;
				count = count_walk;
				
			} else {
				mov = shoot_mov;
				count = count_shoot;
				count_shoot++;
			}
		}
				
		if (is_jumping && count_jump < 12) {
			if (count_jump == 0) {
				if (dir_x != 0) {
					if (flip == 0) {
						dir_x = 10;
					} else {
						dir_x = -10;
					}
				}
				dir_y = -8;
			} else if (count_jump == 6) {
				dir_y = 8;
			}
			mov = jump_mov;
			count = count_jump;
			count_jump++;			
		} else if (is_jumping) {
			is_jumping = false;
			count_jump = 0;
			dir_y = 0;
			mov = walk_mov;
			count = count_walk;
		}
		
		it = this->pj.img_coords(mov, count);
		pixel_x = it->getX();
		pixel_y = it->getY();
		pixel_width = it->getWidth();
		pixel_height = it->getHeight();
			
		
		
		window_width = window.GetWidth();
		window_height = window.GetHeight();
		
		if (pos_x + (dir_x * speed_run) > window_width / 4 * 2 || (pos_x + (dir_x * speed_run) < window_width / 4 && dir_x < 0)) {
			if (pixel_x_screen + dir_x > img_width - pixel_width_screen) {
				pixel_x_screen = 0;
			} else if (pixel_x_screen < 0) {
				pixel_x_screen = img_width - pixel_width_screen;
			} else {
				pixel_x_screen += dir_x;
			}
		} else {
			pos_x += (dir_x * speed_run);
		}

		if (pos_y + dir_y > window_height / 4 * 2 || (pos_y + dir_y < window_height / 4 && dir_y < 0)) {
			if (pixel_y_screen + dir_y > img_height - pixel_height_screen) {
				pixel_y_screen = 0;
			} else if (pixel_y_screen < 0) {
				pixel_y_screen = img_height - pixel_height_screen;
			} else {
				pixel_y_screen += dir_y;
			}
		} else {
			pos_y += dir_y;
		}


		
		renderer.Clear();
		
		
		renderer.Copy(background, SDL2pp::Rect(pixel_x_screen, pixel_y_screen, pixel_width_screen, pixel_height_screen), SDL2pp::Rect(0, 0, window_width, window_height)); 


		SDL2pp::Rect player_rect = SDL2pp::Rect(pos_x, pos_y, 50, 80);
		
		this->points.verify_point_obtained(player_rect);
		
		
		renderer.Copy(jazz_sprite, SDL2pp::Rect(pixel_x, pixel_y, pixel_width, pixel_height), player_rect, 0.0, SDL2pp::NullOpt, flip);
		
		
		this->pj.draw_projectiles(window, renderer, projectile);
		
		this->turtle.draw_enemy(window, renderer, turtle_enemy, 0);
		
		this->schartz_guard.draw_enemy(window, renderer, schartzenguard, 1);
		
		this->yellowM.draw_enemy(window, renderer, yellowMonster, 0);
		
		this->points.draw_points(renderer, items);
		
		
		
		renderer.Present();
		
		SDL_Delay(70);
		
	}
	return;
}




