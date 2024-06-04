#include "gamescreen.h"

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"

#include "projectile.h"

GameScreen::GameScreen(int character, std::string map):
        pj(character), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0) {}

void GameScreen::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::SDLTTF ttf;

    SDL2pp::Window window("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 500,
                          SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Texture background(renderer, "../assets/Tilesets/BeachWorld-1.png");  // FONDO DE PRUEBA

    SDL2pp::Texture jazz_sprite(renderer, SDL2pp::Surface(this->pj.getPath()));
    SDL2pp::Texture turtle_enemy(renderer, SDL2pp::Surface(this->turtle.getPath()));
    SDL2pp::Texture schartzenguard(renderer, SDL2pp::Surface(this->schartz_guard.getPath()));
    SDL2pp::Texture yellowMonster(renderer, SDL2pp::Surface(this->yellowM.getPath()));
    SDL2pp::Texture projectile(renderer, "../assets/Miscellaneous/SFX.png");
    SDL2pp::Texture items(renderer, "../assets/Miscellaneous/Items&Objects.png");


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

    std::list<Sprite>::iterator it = this->pj.img_coords(walk_mov, count_walk);
    int pixel_x = it->x;
    int pixel_y = it->y;
    int pixel_width = it->width;
    int pixel_height = it->height;


    int flip = 0;

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
                        is_walking = false;
                        break;
                }
            }
        }

        renderer.Clear();

        renderer.Copy(background, SDL2pp::Rect(0, 420, 200, 200), SDL2pp::Rect(0, 0, 800, 500));


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
        pixel_x = it->x;
        pixel_y = it->y;
        pixel_width = it->width;
        pixel_height = it->height;


        if (0 <= pos_x + (dir_x * speed_run) < 750 && 0 <= pos_y + dir_y < 450) {
            pos_x += (dir_x * speed_run);
            pos_y += dir_y;
        }

        SDL2pp::Rect player_rect = SDL2pp::Rect(pos_x, pos_y, 50, 80);

        this->points.verify_point_obtained(player_rect);

        renderer.Copy(jazz_sprite, SDL2pp::Rect(pixel_x, pixel_y, pixel_width, pixel_height),
                      player_rect, 0.0, SDL2pp::NullOpt, flip);


        this->pj.draw_projectiles(renderer, projectile);

        this->turtle.draw_enemy(renderer, turtle_enemy, 0);

        this->schartz_guard.draw_enemy(renderer, schartzenguard, 1);

        this->yellowM.draw_enemy(renderer, yellowMonster, 0);

        this->points.draw_points(renderer, items);

        renderer.Present();

        SDL_Delay(70);
    }

    return;
}
