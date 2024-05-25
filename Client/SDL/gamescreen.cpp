#include "gamescreen.h"
#include "projectile.h"

#include <SDL2pp/SDL2pp.hh>

#include <iterator>
#include <map>
#include <vector>

#include <iostream>

GameScreen::GameScreen(int character, std::string map): pj(character), turtle(0), schartz_guard(1), yellowM(2) {
	
}

void GameScreen::run() {
	SDL2pp::SDL sdl(SDL_INIT_VIDEO);
	SDL2pp::SDLTTF ttf;
		
	SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 500, SDL_WINDOW_RESIZABLE);

	SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		
	SDL2pp::Texture background(renderer, "../assets/Tilesets/BeachWorld-1.png"); //FONDO DE PRUEBA
 	
 	SDL2pp::Texture jazz_sprite(renderer, SDL2pp::Surface(this->pj.getPath()));	
	SDL2pp::Texture turtle_enemy(renderer, SDL2pp::Surface(this->turtle.getPath()));
	SDL2pp::Texture schartzenguard(renderer, SDL2pp::Surface(this->schartz_guard.getPath()));
	SDL2pp::Texture yellowMonster(renderer, SDL2pp::Surface(this->yellowM.getPath()));
	SDL2pp::Texture projectile(renderer, "../assets/Miscellaneous/SFX.png");
	

	int walk_mov = 0;
	int count_walk = 0;

	int shoot_mov = 1;
	int count_shoot = 0;
	
	int run_mov = 2;
	int count_run = 0;
	
	int jump_mov = 3;
	int count_jump = 0;
	
	bool is_walking = false;
	bool is_running = false;
	bool is_shooting = false;
	bool is_jumping = false;

		
	int dir_x = 0;
	int dir_y = 0;
	int speed_run = 1;
	
	int pos_x = 0;
	int pos_y = 0;

	
	int pixel_x = 0;
	int pixel_y = this->pj.getYsrc(walk_mov);
	std::map<int, int>::iterator it = this->pj.widthSrc(walk_mov, count_walk); 
	int pixel_width = it->second;
	int pixel_height = this->pj.heightSrc(walk_mov);
	
	int flip = 0;
	
	
	int turtle_count = 0;
	int turtle_x = 0;
	int turtle_y = 200;
	
	int schartzguard_count = 0;
	int sch_guard_x = 0;
	int sch_guard_y = 400;
	
	int yellowm_count = 0;
	int yellowm_x = 0;
	int yellowm_y = 100;
	
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
						speed_run = 3;
						is_running = true;
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
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT: case SDLK_LEFT: 
						is_walking = false;
						dir_x = 0;
						break;
				 	case SDLK_LSHIFT:
						is_running = false;
						count_run = 0;
						speed_run = 1;
						pixel_x = 0;
						pixel_y = this->pj.getYsrc(walk_mov);
						it = this->pj.widthSrc(walk_mov, count_walk); 
						pixel_width = it->second;
						pixel_height = this->pj.heightSrc(walk_mov);

					case SDLK_UP: case SDLK_DOWN:
						dir_y = 0;
						break;
				}
			}
		}
		
		renderer.Clear();
		
		renderer.Copy(background, SDL2pp::Rect(0, 420, 200, 200), SDL2pp::Rect(0, 0, 800, 500));  
		
		
		
		int mov = walk_mov;
		if (is_running) {
			mov = run_mov;
		}
		if (is_walking || is_running) {		
			int count;
			if (is_running) {
				count = count_run;
			} else {
				count = count_walk;
			}
			it = this->pj.widthSrc(mov, count);
			if (count == 0) {
				pixel_y = this->pj.getYsrc(mov);
				pixel_height = this->pj.heightSrc(mov);
				pixel_x = 0;
				pixel_width = it->second;
			} else {
				pixel_x = it->first;
				pixel_width = it->second;
			}
			if (is_running) {
				count_run++;
			} else {
				count_walk++;
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
				it = this->pj.widthSrc(walk_mov, count_walk);
				count_shoot = 0;
				is_shooting = false; 
				pixel_width = it->second;
				pixel_y = this->pj.getYsrc(walk_mov);
				pixel_height = this->pj.heightSrc(walk_mov);
				pixel_x = 0;	
			} else {
				it = this->pj.widthSrc(shoot_mov, count_shoot);
				if (count_shoot == 0) {
					pixel_y = this->pj.getYsrc(shoot_mov);
					pixel_height = this->pj.heightSrc(shoot_mov);
					pixel_x = 0; 					
				} else {
					pixel_x = it->first;
				}
				pixel_width = it->second;
				count_shoot++;
			}
		}
				
		if (is_jumping && count_jump < 12) {
			it = this->pj.widthSrc(jump_mov, count_jump);		
			if (count_jump == 0) {
				pixel_y = this->pj.getYsrc(jump_mov);
				pixel_height = this->pj.heightSrc(jump_mov);
				pixel_x = 0;
				if (dir_x != 0) {
					if (flip == 0) {
						dir_x = 10;
					} else {
						dir_x = -10;
					}
				}
				dir_y = -8;
			} else {
				pixel_x = it->first;
			}
			if (count_jump == 6) {
				dir_y = 8;
			}
			pixel_width = it->second;
			count_jump++;			
		} else if (is_jumping) {
			is_jumping = false;
			count_jump = 0;
			dir_y = 0;
			pixel_x = 0;
			pixel_y = this->pj.getYsrc(walk_mov);
			it = this->pj.widthSrc(walk_mov, count_walk); 
			pixel_width = it->second;
			pixel_height = this->pj.heightSrc(walk_mov);		
		}
		

		
		if (0 <= pos_x + (dir_x * speed_run) <= 750 && 0 <= pos_y + dir_y <= 450) {		
			pos_x += (dir_x * speed_run);
			pos_y += dir_y;
		}	


		std::map<int, int>::iterator it2 = this->turtle.widthSrc(0, turtle_count); 
		int turtle_pixel_x = it2->first;
		int turtle_pixel_w = it2->second;
		int turtle_pixel_y = this->turtle.getYsrc(0);
		int turtle_pixel_h = this->turtle.heightSrc(0);


		std::map<int, int>::iterator it3 = this->schartz_guard.widthSrc(0, schartzguard_count); 
		int schguard_pixel_x = it3->first;
		int schguard_pixel_w = it3->second;
		int schguard_pixel_y = this->schartz_guard.getYsrc(0);
		int schguard_pixel_h = this->schartz_guard.heightSrc(0);


		std::map<int, int>::iterator it4 = this->yellowM.widthSrc(0, yellowm_count); 
		int yellowm_pixel_x = it4->first;
		int yellowm_pixel_w = it4->second;		
		int yellowm_pixel_y = this->yellowM.getYsrc(0);
		int yellowm_pixel_h = this->yellowM.heightSrc(0);

			
		renderer.Copy(jazz_sprite, SDL2pp::Rect(pixel_x, pixel_y, pixel_width, pixel_height), 
			SDL2pp::Rect(pos_x, pos_y, 50, 80), 0.0, SDL2pp::NullOpt, flip);
		
		renderer.Copy(turtle_enemy, SDL2pp::Rect(turtle_pixel_x, turtle_pixel_y, turtle_pixel_w, turtle_pixel_h), SDL2pp::Rect(turtle_x, turtle_y, 50, 50), 0.0, SDL2pp::NullOpt, 0);
		
		renderer.Copy(schartzenguard, SDL2pp::Rect(schguard_pixel_x, schguard_pixel_y, schguard_pixel_w, schguard_pixel_h), SDL2pp::Rect(sch_guard_x, sch_guard_y, 60, 100), 0.0, SDL2pp::NullOpt, 0);
		
		renderer.Copy(yellowMonster, SDL2pp::Rect(yellowm_pixel_x, yellowm_pixel_y, yellowm_pixel_w, yellowm_pixel_h), SDL2pp::Rect(yellowm_x, yellowm_y, 30, 50), 0.0, SDL2pp::NullOpt, 0);
		
		this->pj.draw_projectiles(renderer, projectile);
		
				
		if (turtle_x > 800) {
			turtle_x = -50;
		} else {
			turtle_x += 1;
		}
		turtle_count++;
		
		if (sch_guard_x > 800) {
			sch_guard_x = -50;
		} else {
			sch_guard_x += 2;
		}
		schartzguard_count++;
		
		if (yellowm_x > 800) {
			yellowm_x = -50;
		} else {
			yellowm_x += 5;
		}
		yellowm_count++;
		
		
		renderer.Present();
		
		SDL_Delay(70);
		
	}
	
	return;
}
