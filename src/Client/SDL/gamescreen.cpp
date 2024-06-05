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

GameScreen::GameScreen(int character, std::string map):
        pj(character), turtle(0, 0, 200), schartz_guard(1, 0, 400), yellowM(2, 0, 100), points(0) {}

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

    SDL_Surface* turtle_surf = IMG_Load(this->turtle.getPath().c_str());
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

        if (pos_x + (dir_x * speed_run) > window_width / 4 * 2 ||
            (pos_x + (dir_x * speed_run) < window_width / 4 && dir_x < 0)) {
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

        if (pos_y + dir_y > window_height / 4 * 2 ||
            (pos_y + dir_y < window_height / 4 && dir_y < 0)) {
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

        renderer.Copy(background,
                      SDL2pp::Rect(pixel_x_screen, pixel_y_screen, pixel_width_screen,
                                   pixel_height_screen),
                      SDL2pp::Rect(0, 0, window_width, window_height));

        SDL2pp::Rect player_rect = SDL2pp::Rect(pos_x, pos_y, 50, 80);

        this->points.verify_point_obtained(player_rect);

        renderer.Copy(jazz_sprite, SDL2pp::Rect(pixel_x, pixel_y, pixel_width, pixel_height),
                      player_rect, 0.0, SDL2pp::NullOpt, flip);

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




