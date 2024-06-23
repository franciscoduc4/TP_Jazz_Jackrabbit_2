#include "level.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Common/Config/ClientConfig.h"


#include <iostream>
#include <cmath>

enum lvl { BEACH, HOLIDAIUS, COLONIUS };

Level::Level(uint8_t level) {
    std::vector<ObstacleType> tiles_types{ ObstacleType::BACKGROUND, ObstacleType::FULL_FLOOR, ObstacleType::LONG_PLATFORM, 
    ObstacleType::SMALL_PLATFORM, ObstacleType::COLUMN, ObstacleType::LEFT_LADDER, ObstacleType::RIGHT_LADDER };
    std::vector<std::string> tilesSprites;
    std::vector<std::vector<int>> beachSprites;
    std::vector<std::vector<int>> widthsHeights; 
    switch (level) {
        case HOLIDAIUS:
            tilesSprites = ClientConfig::getHolidaiusFiles();
            beachSprites = ClientConfig::getHolidaiusSprites();
            widthsHeights = ClientConfig::getHolidaiusWidthHeightSprites();
            for (int i = 0; i < tilesSprites.size(); i++) {
                this->paths[tiles_types[i]] = tilesSprites[i];
                this->pixels_pos[tiles_types[i]] = beachSprites[i];
                this->width_height[tiles_types[i]] = widthsHeights[i];
            }
            break;
        case COLONIUS:
            tilesSprites = ClientConfig::getColoniusFiles();
            beachSprites = ClientConfig::getColoniusSprites();
            widthsHeights = ClientConfig::getColoniusWidthHeightSprites();
            for (int i = 0; i < tilesSprites.size(); i++) {
                this->paths[tiles_types[i]] = tilesSprites[i];
                this->pixels_pos[tiles_types[i]] = beachSprites[i];
                this->width_height[tiles_types[i]] = widthsHeights[i];
            }
            //this->max_pixel_x_floor = 2000;
            //this->floor_height = 100;
            //this->background_width = 2000;
            //this->background_height = 839;
            break;
        default:
            tilesSprites = ClientConfig::getBeachFiles();
            beachSprites = ClientConfig::getBeachSprites();
            widthsHeights = ClientConfig::getBeachWidthHeightSprites();
            for (int i = 0; i < tilesSprites.size(); i++) {
                this->paths[tiles_types[i]] = tilesSprites[i];
                this->pixels_pos[tiles_types[i]] = beachSprites[i];
                this->width_height[tiles_types[i]] = widthsHeights[i];
            }
            //this->max_pixel_x_floor = 2491;
            //this->floor_height = 70;
            //this->background_width = 715;
            //this->background_height = 153;
            break;
        

    }
}

std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>> Level::getTilesTextures(SDL2pp::Renderer& renderer)  {
    std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>> textures;

    SDL_Surface* bg_surf = IMG_Load(this->paths[ObstacleType::BACKGROUND].c_str());
    SDL2pp::Surface backgroundSurface(bg_surf);
    backgroundSurface.SetColorKey(true, SDL_MapRGB(backgroundSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::BACKGROUND] = std::make_unique<SDL2pp::Texture>(renderer, backgroundSurface);

    
    SDL_Surface* floor_surf = IMG_Load(this->paths[ObstacleType::FULL_FLOOR].c_str());
    SDL2pp::Surface floorSurface(floor_surf);
    floorSurface.SetColorKey(true, SDL_MapRGB(floorSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::FULL_FLOOR] =  std::make_unique<SDL2pp::Texture>(renderer, floorSurface);

    SDL_Surface* longPlatform_surf = IMG_Load(this->paths[ObstacleType::LONG_PLATFORM].c_str());
    SDL2pp::Surface longPlatformSurface(longPlatform_surf);
    longPlatformSurface.SetColorKey(true, SDL_MapRGB(longPlatformSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::LONG_PLATFORM] = std::make_unique<SDL2pp::Texture>(renderer, longPlatformSurface);
    
    SDL_Surface* smallPlatform_surf = IMG_Load(this->paths[ObstacleType::SMALL_PLATFORM].c_str());
    SDL2pp::Surface smallPlatformSurface(smallPlatform_surf);
    smallPlatformSurface.SetColorKey(true, SDL_MapRGB(smallPlatformSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::SMALL_PLATFORM] = std::make_unique<SDL2pp::Texture>(renderer, smallPlatformSurface);
    
    SDL_Surface* column_surf = IMG_Load(this->paths[ObstacleType::COLUMN].c_str());
    SDL2pp::Surface columnSurface(column_surf);
    columnSurface.SetColorKey(true, SDL_MapRGB(columnSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::COLUMN] = std::make_unique<SDL2pp::Texture>(renderer, columnSurface);

    SDL_Surface* leftDiagonal_surf = IMG_Load(this->paths[ObstacleType::LEFT_LADDER].c_str());
    SDL2pp::Surface leftDiagonalSurface(leftDiagonal_surf);
    leftDiagonalSurface.SetColorKey(true, SDL_MapRGB(leftDiagonalSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::LEFT_LADDER] = std::make_unique<SDL2pp::Texture>(renderer, leftDiagonalSurface);

    SDL_Surface* rightDiagonal_surf = IMG_Load(this->paths[ObstacleType::RIGHT_LADDER].c_str());
    SDL2pp::Surface rightDiagonalSurface(rightDiagonal_surf);
    rightDiagonalSurface.SetColorKey(true, SDL_MapRGB(rightDiagonalSurface.Get()->format, 87, 0, 203));
    textures[ObstacleType::RIGHT_LADDER] = std::make_unique<SDL2pp::Texture>(renderer, rightDiagonalSurface);
    
    return textures;
}


std::string Level::getLevelPath(ObstacleType type) {
    return this->paths[type];
}

std::vector<int> Level::draw_background(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>>& textures, PlayerDTO& player) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    int index_draw_width = 0;
    int index_draw_height = 1;
    int window_width = window.GetWidth();
    int window_height = window.GetHeight();
    std::vector<int> dir_screen{0, 0};
    renderer.Copy(*textures[ObstacleType::BACKGROUND],
                      SDL2pp::Rect(this->pixels_pos[ObstacleType::BACKGROUND][index_x], this->pixels_pos[ObstacleType::BACKGROUND][index_y], this->pixels_pos[ObstacleType::BACKGROUND][index_width], this->pixels_pos[ObstacleType::BACKGROUND][index_height]),
                      SDL2pp::Rect(0, 0, window_width, window_height));
    uint32_t get_pos_x = player.getX();
    uint32_t get_pos_y = player.getY();
    int get_speed = player.getSpeed();

    
    if (get_pos_x > window_width / 2) {
        if (pixels_pos[ObstacleType::BACKGROUND][index_x] + get_speed > this->width_height[ObstacleType::BACKGROUND][index_draw_width] - pixels_pos[ObstacleType::BACKGROUND][index_width]) {
            pixels_pos[ObstacleType::BACKGROUND][index_x] = 0;
        } else if (pixels_pos[ObstacleType::BACKGROUND][index_x] < 0) {
            pixels_pos[ObstacleType::BACKGROUND][index_x] = this->width_height[ObstacleType::BACKGROUND][index_draw_width] - pixels_pos[ObstacleType::BACKGROUND][index_width];
        } else {
            pixels_pos[ObstacleType::BACKGROUND][index_x] += get_speed;
        }
        dir_screen[0] = window_width / 2;
    }

    if (get_pos_y > window_height / 2) {
        if (pixels_pos[ObstacleType::BACKGROUND][index_y] + get_speed > this->width_height[ObstacleType::BACKGROUND][index_draw_height] - pixels_pos[ObstacleType::BACKGROUND][index_height]) {
            pixels_pos[ObstacleType::BACKGROUND][index_y] = 0;
        } else if (pixels_pos[ObstacleType::BACKGROUND][index_y] < 0) {
            pixels_pos[ObstacleType::BACKGROUND][index_y] = this->width_height[ObstacleType::BACKGROUND][index_draw_height] - pixels_pos[ObstacleType::BACKGROUND][index_height];
        } else {
            pixels_pos[ObstacleType::BACKGROUND][index_y] += get_speed;
        }
        dir_screen[1] = window_height / 2;
    }
    return dir_screen;

}

void Level::draw_floor(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>>& textiles, int player_speed) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    int index_draw_height = 1;
    
    if (this->pixels_pos[ObstacleType::FULL_FLOOR][index_x] > this->max_pixel_x_floor - this->pixels_pos[ObstacleType::FULL_FLOOR][index_width]) {
        this->pixels_pos[ObstacleType::FULL_FLOOR][index_x] = 0;
    }

    renderer.Copy(*textiles[ObstacleType::FULL_FLOOR], SDL2pp::Rect(this->pixels_pos[ObstacleType::FULL_FLOOR][index_x], this->pixels_pos[ObstacleType::FULL_FLOOR][index_y], this->pixels_pos[ObstacleType::FULL_FLOOR][index_width], this->pixels_pos[ObstacleType::FULL_FLOOR][index_height]), 
                        SDL2pp::Rect(0, window.GetHeight() - this->width_height[ObstacleType::FULL_FLOOR][index_draw_height], window.GetWidth(), this->width_height[ObstacleType::FULL_FLOOR][index_draw_height]));
    this->pixels_pos[ObstacleType::FULL_FLOOR][index_x] += player_speed;
}


void Level::draw_tiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<ObstacleType, std::unique_ptr<SDL2pp::Texture>>& tiles_textures, std::vector<TileDTO>& tiles, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    
    int index_draw_width = 0;
    int index_draw_height = 1;

    int distance_tile_player_x = 0;
    int distance_tile_player_y = 0;

    for (auto t: tiles) {
        uint32_t x = t.getX();
        uint32_t y = t.getY();
        
        if (dir_x_screen != 0) { 
            distance_tile_player_x = x - player.getX();
            x = dir_x_screen + distance_tile_player_x;
        }
        if (dir_y_screen != 0) {
            distance_tile_player_y = y - player.getX();
            y = dir_y_screen + distance_tile_player_y;
        }
		
        
        if (abs(distance_tile_player_x) <= window.GetWidth()  && abs(distance_tile_player_y) <= window.GetHeight()) {
            ObstacleType type = t.getObstacleType();
            renderer.Copy(*tiles_textures[type], SDL2pp::Rect(pixels_pos[type][index_x], pixels_pos[type][index_y], pixels_pos[type][index_width], pixels_pos[type][index_height]), SDL2pp::Rect(x, y, this->width_height[type][index_draw_width], this->width_height[type][index_draw_height]));
        } 

    }
}