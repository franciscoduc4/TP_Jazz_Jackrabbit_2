#include "level.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Common/Config/ClientConfig.h"


#include <iostream>
#include <cmath>

enum lvl { BEACH, HOLIDAIUS, COLONIUS };

Level::Level(uint8_t level) {
    /* std::vector<int> backVector{0, 0, 200, 160};
    std::vector<int> floorVector{0, 0, 485, 118};
    std::vector<int> longPlatformVector{0, 0, 160, 17};
    std::vector<int> smallPlatformVector{0, 0, 88, 17};
    std::vector<int> columnVector{0, 0, 24, 91};
    std::vector<int> leftLadderVector{0, 0, 145, 145};
    std::vector<int> rightLadderVector{0, 0, 144, 165};
    */
    std::vector<TileType> tiles_types{ TileType::BACKGROUND, TileType::FLOOR, TileType::LONGPLATFORM, TileType::SMALLPLATFORM, TileType::COLUMN, TileType::LEFTDIAGONAL, TileType::RIGHTDIAGONAL };
    std::vector<std::string> tilesSprites;
    std::vector<std::vector<int>> beachSprites;
    switch (level) {
        case BEACH:
            tilesSprites = ClientConfig::getBeachFiles();
            beachSprites = ClientConfig::getBeachSprites();
            for (int i = 0; i < tilesSprites.size(); i++) {
                this->paths[tiles_types[i]] = tilesSprites[i];
                this->pixels_pos[tiles_types[i]] = beachSprites[i];
            }
            /*
            this->paths[TileType::BACKGROUND] = "../assets/scenes/BeachWorld/background.png";
            this->pixels_pos[TileType::BACKGROUND] = backVector;
            
            this->paths[TileType::FLOOR] = "../assets/scenes/BeachWorld/fullFloor.png";
            this->pixels_pos[TileType::FLOOR] = floorVector;

            this->paths[TileType::LONGPLATFORM] = "../assets/scenes/BeachWorld/longPlatform.png";
            this->pixels_pos[TileType::LONGPLATFORM] = longPlatformVector;
            this->width_height[TileType::LONGPLATFORM] = {150, 30};

            this->paths[TileType::SMALLPLATFORM] = "../assets/scenes/BeachWorld/smallPlatform.png";
            this->pixels_pos[TileType::SMALLPLATFORM] = smallPlatformVector;
            this->width_height[TileType::SMALLPLATFORM] = {70, 30};

            this->paths[TileType::COLUMN] = "../assets/scenes/BeachWorld/woodLargeColumn.png";
            this->pixels_pos[TileType::COLUMN] = columnVector;
            this->width_height[TileType::COLUMN] = {30, 100};

            this->paths[TileType::LEFTDIAGONAL] = "../assets/scenes/BeachWorld/leftLadder.png";
            this->pixels_pos[TileType::LEFTDIAGONAL] = leftLadderVector;
            this->width_height[TileType::LEFTDIAGONAL] = {120, 120};

            this->paths[TileType::RIGHTDIAGONAL] = "../assets/scenes/BeachWorld/rightLadder.png";
            this->pixels_pos[TileType::RIGHTDIAGONAL] = rightLadderVector;
            this->width_height[TileType::RIGHTDIAGONAL] = {120, 120};
            */
            this->max_pixel_x_floor = 2491;
            this->floor_height = 70;
            this->background_width = 715;
            this->background_height = 153;
            break;
        case HOLIDAIUS:
            break;
        case COLONIUS:
            tilesSprites = ClientConfig::getColoniusFiles();
            beachSprites = ClientConfig::getColoniusSprites();
            for (int i = 0; i < tilesSprites.size(); i++) {
                this->paths[tiles_types[i]] = tilesSprites[i];
                this->pixels_pos[tiles_types[i]] = beachSprites[i];
            }
            this->max_pixel_x_floor = 2000;
            this->floor_height = 100;

            this->background_width = 2000;
            this->background_height = 839;
            break;
    }
}

std::map<TileType, std::unique_ptr<SDL2pp::Texture>> Level::getTilesTextures(SDL2pp::Renderer& renderer)  {
    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> textures;

    SDL_Surface* bg_surf = IMG_Load(this->paths[TileType::BACKGROUND].c_str());
    SDL2pp::Surface backgroundSurface(bg_surf);
    backgroundSurface.SetColorKey(true, SDL_MapRGB(backgroundSurface.Get()->format, 87, 0, 203));
    textures[TileType::BACKGROUND] = std::make_unique<SDL2pp::Texture>(renderer, backgroundSurface);

    
    SDL_Surface* floor_surf = IMG_Load(this->paths[TileType::FLOOR].c_str());
    SDL2pp::Surface floorSurface(floor_surf);
    floorSurface.SetColorKey(true, SDL_MapRGB(floorSurface.Get()->format, 87, 0, 203));
    textures[TileType::FLOOR] =  std::make_unique<SDL2pp::Texture>(renderer, floorSurface);

    SDL_Surface* longPlatform_surf = IMG_Load(this->paths[TileType::LONGPLATFORM].c_str());
    SDL2pp::Surface longPlatformSurface(longPlatform_surf);
    longPlatformSurface.SetColorKey(true, SDL_MapRGB(longPlatformSurface.Get()->format, 87, 0, 203));
    textures[TileType::LONGPLATFORM] = std::make_unique<SDL2pp::Texture>(renderer, longPlatformSurface);
    
    SDL_Surface* smallPlatform_surf = IMG_Load(this->paths[TileType::SMALLPLATFORM].c_str());
    SDL2pp::Surface smallPlatformSurface(smallPlatform_surf);
    smallPlatformSurface.SetColorKey(true, SDL_MapRGB(smallPlatformSurface.Get()->format, 87, 0, 203));
    textures[TileType::SMALLPLATFORM] = std::make_unique<SDL2pp::Texture>(renderer, smallPlatformSurface);
    
    SDL_Surface* column_surf = IMG_Load(this->paths[TileType::COLUMN].c_str());
    SDL2pp::Surface columnSurface(column_surf);
    columnSurface.SetColorKey(true, SDL_MapRGB(columnSurface.Get()->format, 87, 0, 203));
    textures[TileType::COLUMN] = std::make_unique<SDL2pp::Texture>(renderer, columnSurface);

    SDL_Surface* leftDiagonal_surf = IMG_Load(this->paths[TileType::LEFTDIAGONAL].c_str());
    SDL2pp::Surface leftDiagonalSurface(leftDiagonal_surf);
    leftDiagonalSurface.SetColorKey(true, SDL_MapRGB(leftDiagonalSurface.Get()->format, 87, 0, 203));
    textures[TileType::LEFTDIAGONAL] = std::make_unique<SDL2pp::Texture>(renderer, leftDiagonalSurface);

    SDL_Surface* rightDiagonal_surf = IMG_Load(this->paths[TileType::RIGHTDIAGONAL].c_str());
    SDL2pp::Surface rightDiagonalSurface(rightDiagonal_surf);
    rightDiagonalSurface.SetColorKey(true, SDL_MapRGB(rightDiagonalSurface.Get()->format, 87, 0, 203));
    textures[TileType::RIGHTDIAGONAL] = std::make_unique<SDL2pp::Texture>(renderer, rightDiagonalSurface);
    
    return textures;
}


std::string Level::getLevelPath(TileType type) {
    return this->paths[type];
}

std::vector<int> Level::draw_background(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& textures, PlayerDTO& player) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    int window_width = window.GetWidth();
    int window_height = window.GetHeight();
    std::vector<int> dir_screen{0, 0};
    renderer.Copy(*textures[TileType::BACKGROUND],
                      SDL2pp::Rect(this->pixels_pos[TileType::BACKGROUND][index_x], this->pixels_pos[TileType::BACKGROUND][index_y], this->pixels_pos[TileType::BACKGROUND][index_width], this->pixels_pos[TileType::BACKGROUND][index_height]),
                      SDL2pp::Rect(0, 0, window_width, window_height));
    uint32_t get_pos_x = player.getX();
    uint32_t get_pos_y = player.getY();
    int get_speed = player.getSpeed();
        
    if (get_pos_x > window_width / 2) {
        if (pixels_pos[TileType::BACKGROUND][index_x] + get_speed > this->background_width - pixels_pos[TileType::BACKGROUND][index_width]) {
            pixels_pos[TileType::BACKGROUND][index_x] = 0;
        } else if (pixels_pos[TileType::BACKGROUND][index_x] < 0) {
            pixels_pos[TileType::BACKGROUND][index_x] = this->background_width - pixels_pos[TileType::BACKGROUND][index_width];
        } else {
            pixels_pos[TileType::BACKGROUND][index_x] += get_speed;
        }
        dir_screen[0] = window_width / 2;
    }

    if (get_pos_y > window_height / 2) {
        if (pixels_pos[TileType::BACKGROUND][index_y] + get_speed > this->background_height - pixels_pos[TileType::BACKGROUND][index_height]) {
            pixels_pos[TileType::BACKGROUND][index_y] = 0;
        } else if (pixels_pos[TileType::BACKGROUND][index_y] < 0) {
            pixels_pos[TileType::BACKGROUND][index_y] = this->background_height - pixels_pos[TileType::BACKGROUND][index_height];
        } else {
            pixels_pos[TileType::BACKGROUND][index_y] += get_speed;
        }
        dir_screen[1] = window_height / 2;
    }
    return dir_screen;

}

void Level::draw_floor(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& textiles, int player_speed) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    
    if (this->pixels_pos[TileType::FLOOR][index_x] > this->max_pixel_x_floor - this->pixels_pos[TileType::FLOOR][index_width]) {
        this->pixels_pos[TileType::FLOOR][index_x] = 0;
    }

    renderer.Copy(*textiles[TileType::FLOOR], SDL2pp::Rect(this->pixels_pos[TileType::FLOOR][index_x], this->pixels_pos[TileType::FLOOR][index_y], this->pixels_pos[TileType::FLOOR][index_width], this->pixels_pos[TileType::FLOOR][index_height]), 
                        SDL2pp::Rect(0, window.GetHeight() - this->floor_height, window.GetWidth(), this->floor_height));
    this->pixels_pos[TileType::FLOOR][index_x] += player_speed;
}


void Level::draw_tiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& tiles_textures, std::vector<TileDTO>& tiles, PlayerDTO& player) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    
    int index_draw_width = 0;
    int index_draw_height = 1;
    for (auto t: tiles) {
        int distance_tile_player_x = player.getX() - t.getX();
        int distance_tile_player_y = player.getY() - t.getY();

        if (abs(distance_tile_player_x) <= window.GetWidth() / 2  && abs(distance_tile_player_y) <= window.GetHeight() / 2) {
            //TileType type = t.getType();
            //renderer.Copy(*tiles_textures[TileType::LONGPLATFORM/*type*/], SDL2pp::Rect(pixels_pos[TileType::LONGPLATFORM/*type*/][index_x], pixels_pos[TileType::LONGPLATFORM/*type*/][index_y], pixels_pos[TileType::LONGPLATFORM/*type*/][index_width], pixels_pos[TileType::LONGPLATFORM/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::LONGPLATFORM/*type*/][index_draw_width], this->width_height[TileType::LONGPLATFORM/*type*/][index_draw_height]));
            //renderer.Copy(*tiles_textures[TileType::SMALLPLATFORM/*type*/], SDL2pp::Rect(pixels_pos[TileType::SMALLPLATFORM/*type*/][index_x], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_y], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_width], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::SMALLPLATFORM/*type*/][index_draw_width], this->width_height[TileType::SMALLPLATFORM/*type*/][index_draw_height]));
            //renderer.Copy(*tiles_textures[TileType::COLUMN/*type*/], SDL2pp::Rect(pixels_pos[TileType::COLUMN/*type*/][index_x], pixels_pos[TileType::COLUMN/*type*/][index_y], pixels_pos[TileType::COLUMN/*type*/][index_width], pixels_pos[TileType::COLUMN/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::COLUMN/*type*/][index_draw_width], this->width_height[TileType::COLUMN/*type*/][index_draw_height]));
            //renderer.Copy(*tiles_textures[TileType::LEFTDIAGONAL/*type*/], SDL2pp::Rect(pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_x], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_y], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_width], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::LEFTDIAGONAL/*type*/][index_draw_width], this->width_height[TileType::LEFTDIAGONAL/*type*/][index_draw_height]));
            renderer.Copy(*tiles_textures[TileType::RIGHTDIAGONAL/*type*/], SDL2pp::Rect(pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_x], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_y], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_width], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::RIGHTDIAGONAL/*type*/][index_draw_width], this->width_height[TileType::RIGHTDIAGONAL/*type*/][index_draw_height]));
        }
    }
}