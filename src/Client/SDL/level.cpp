#include "level.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include <iostream>


enum lvl { BEACH };
enum tile_type { Background, Floor, LongPlatform, SmallPlatform, Column, LeftDiagonal, RightDiagonal };


Level::Level(int level) {
    std::vector<int> backVector{0, 0, 200, 200};
    std::vector<int> floorVector{0, 0, 485, 118};
    std::vector<int> longPlatformVector{0, 0, 160, 17};
    std::vector<int> smallPlatformVector{0, 0, 88, 17};
    std::vector<int> columnVector{0, 0, 24, 91};
    std::vector<int> leftLadderVector{0, 0, 145, 145};
    std::vector<int> rightLadderVector{0, 0, 144, 165};
    switch (level) {
        case BEACH:
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

            this->max_pixel_x_floor = 2491;
            this->floor_height = 70;
            this->background_width = 256;
            this->background_height = 160;
            break;
    }
}

std::map<TileType, std::unique_ptr<SDL2pp::Texture>> Level::getTilesTextures(SDL2pp::Renderer& renderer)  {
    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> textures;

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

std::vector<int> Level::draw_background(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, PlayerDTO& player) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    int window_width = window.GetWidth();
    int window_height = window.GetHeight();
    std::vector<int> dir_screen{0, 0};
    renderer.Copy(background,
                      SDL2pp::Rect(this->pixels_pos[TileType::BACKGROUND][index_x], this->pixels_pos[TileType::BACKGROUND][index_y], this->pixels_pos[TileType::BACKGROUND][index_width], this->pixels_pos[TileType::BACKGROUND][index_height]),
                      SDL2pp::Rect(0, 0, window_width, window_height));
    uint16_t get_pos_x = player.getX();
    uint16_t get_pos_y = player.getY();
    int get_speed = player.getSpeed();
        
    if (get_pos_x > window_width / 4 * 2 ||
        (get_pos_x < window_width / 4 && get_speed < 0)) {
        if (pixels_pos[TileType::BACKGROUND][index_x] + get_speed > this->background_width - pixels_pos[TileType::BACKGROUND][index_width]) {
            pixels_pos[TileType::BACKGROUND][index_x] = 0;
        } else if (pixels_pos[TileType::BACKGROUND][index_x] < 0) {
            pixels_pos[TileType::BACKGROUND][index_x] = this->background_width - pixels_pos[TileType::BACKGROUND][index_width];
        } else {
            pixels_pos[TileType::BACKGROUND][index_x] += get_speed;
        }
        dir_screen[0] = window_width / 4 * 2;
    }

    if (get_pos_y > window_height / 4 * 2 ||
        (get_pos_y < window_height / 4 && get_speed < 0)) {
        if (pixels_pos[TileType::BACKGROUND][index_y] + get_speed > this->background_height - pixels_pos[TileType::BACKGROUND][index_height]) {
            pixels_pos[TileType::BACKGROUND][index_y] = 0;
        } else if (pixels_pos[TileType::BACKGROUND][index_y] < 0) {
            pixels_pos[TileType::BACKGROUND][index_y] = this->background_height - pixels_pos[TileType::BACKGROUND][index_height];
        } else {
            pixels_pos[TileType::BACKGROUND][index_y] += get_speed;
        }
        dir_screen[1] = window_height / 4 * 2;
    }
    return dir_screen;

}

void Level::draw_floor(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& floor, int player_speed) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    
    if (this->pixels_pos[TileType::FLOOR][index_x] > this->max_pixel_x_floor - this->pixels_pos[TileType::FLOOR][index_width]) {
        this->pixels_pos[TileType::FLOOR][index_x] = 0;
    }

    renderer.Copy(floor, SDL2pp::Rect(this->pixels_pos[TileType::FLOOR][index_x], this->pixels_pos[TileType::FLOOR][index_y], this->pixels_pos[TileType::FLOOR][index_width], this->pixels_pos[TileType::FLOOR][index_height]), 
                        SDL2pp::Rect(0, window.GetHeight() - this->floor_height, window.GetWidth(), this->floor_height));
    this->pixels_pos[TileType::FLOOR][index_x] += player_speed;
}


void Level::draw_tiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& tiles_textures, std::vector<TileDTO>& tiles) {
    int index_x = 0;
    int index_y = 1;
    int index_width = 2;
    int index_height = 3;
    
    int index_draw_width = 0;
    int index_draw_height = 1;
    for (auto t: tiles) {
        //TileType type = t.getType();
        //renderer.Copy(*tiles_textures[TileType::LONGPLATFORM/*type*/], SDL2pp::Rect(pixels_pos[TileType::LONGPLATFORM/*type*/][index_x], pixels_pos[TileType::LONGPLATFORM/*type*/][index_y], pixels_pos[TileType::LONGPLATFORM/*type*/][index_width], pixels_pos[TileType::LONGPLATFORM/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::LONGPLATFORM/*type*/][index_draw_width], this->width_height[TileType::LONGPLATFORM/*type*/][index_draw_height]));
        //renderer.Copy(*tiles_textures[TileType::SMALLPLATFORM/*type*/], SDL2pp::Rect(pixels_pos[TileType::SMALLPLATFORM/*type*/][index_x], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_y], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_width], pixels_pos[TileType::SMALLPLATFORM/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::SMALLPLATFORM/*type*/][index_draw_width], this->width_height[TileType::SMALLPLATFORM/*type*/][index_draw_height]));
        //renderer.Copy(*tiles_textures[TileType::COLUMN/*type*/], SDL2pp::Rect(pixels_pos[TileType::COLUMN/*type*/][index_x], pixels_pos[TileType::COLUMN/*type*/][index_y], pixels_pos[TileType::COLUMN/*type*/][index_width], pixels_pos[TileType::COLUMN/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::COLUMN/*type*/][index_draw_width], this->width_height[TileType::COLUMN/*type*/][index_draw_height]));
        //renderer.Copy(*tiles_textures[TileType::LEFTDIAGONAL/*type*/], SDL2pp::Rect(pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_x], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_y], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_width], pixels_pos[TileType::LEFTDIAGONAL/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::LEFTDIAGONAL/*type*/][index_draw_width], this->width_height[TileType::LEFTDIAGONAL/*type*/][index_draw_height]));
        renderer.Copy(*tiles_textures[TileType::RIGHTDIAGONAL/*type*/], SDL2pp::Rect(pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_x], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_y], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_width], pixels_pos[TileType::RIGHTDIAGONAL/*type*/][index_height]), SDL2pp::Rect(t.getX(), t.getY(), this->width_height[TileType::RIGHTDIAGONAL/*type*/][index_draw_width], this->width_height[TileType::RIGHTDIAGONAL/*type*/][index_draw_height]));
    }
}