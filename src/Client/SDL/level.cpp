#include "level.h"

#include <iostream>


enum lvl { BEACH };
enum tile_type { Background, Floor, Tile };


Level::Level(int level) {
    std::vector<int> backVector{0, 0, 200, 200};
    std::vector<int> floorVector{0, 0, 485, 118};
    switch (level) {
        case BEACH:
            this->paths[Background] = "../assets/scenes/BeachWorld/background.png";
            this->pixels_pos[Background] = backVector;
            
            this->paths[Floor] = "../assets/scenes/BeachWorld/fullFloor.png";
            this->pixels_pos[Floor] = floorVector;

            this->max_pixel_x_floor = 2491;
            this->floor_height = 70;
            this->background_width = 256;
            this->background_height = 160;

            break;
    }
}

std::string Level::getLevelPath(int type) {
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
                      SDL2pp::Rect(this->pixels_pos[Background][index_x], this->pixels_pos[Background][index_y], this->pixels_pos[Background][index_width], this->pixels_pos[Background][index_height]),
                      SDL2pp::Rect(0, 0, window_width, window_height));
    uint16_t get_pos_x = player.getX();
    uint16_t get_pos_y = player.getY();
    int get_speed = player.getSpeed();
        
    if (get_pos_x > window_width / 4 * 2 ||
        (get_pos_x < window_width / 4 && get_speed < 0)) {
        if (pixels_pos[Background][index_x] + get_speed > this->background_width - pixels_pos[Background][index_width]) {
            pixels_pos[Background][index_x] = 0;
        } else if (pixels_pos[Background][index_x] < 0) {
            pixels_pos[Background][index_x] = this->background_width - pixels_pos[Background][index_width];
        } else {
            pixels_pos[Background][index_x] += get_speed;
        }
        dir_screen[0] = window_width / 4 * 2;
    }

    if (get_pos_y > window_height / 4 * 2 ||
        (get_pos_y < window_height / 4 && get_speed < 0)) {
        if (pixels_pos[Background][index_y] + get_speed > this->background_height - pixels_pos[Background][index_height]) {
            pixels_pos[Background][index_y] = 0;
        } else if (pixels_pos[Background][index_y] < 0) {
            pixels_pos[Background][index_y] = this->background_height - pixels_pos[Background][index_height];
        } else {
            pixels_pos[Background][index_y] += get_speed;
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
    
    if (this->pixels_pos[Floor][index_x] > this->max_pixel_x_floor - this->pixels_pos[Floor][index_width]) {
        this->pixels_pos[Floor][index_x] = 0;
    }

    renderer.Copy(floor, SDL2pp::Rect(this->pixels_pos[Floor][index_x], this->pixels_pos[Floor][index_y], this->pixels_pos[Floor][index_width], this->pixels_pos[Floor][index_height]), 
                        SDL2pp::Rect(0, window.GetHeight() - this->floor_height, window.GetWidth(), this->floor_height));
    this->pixels_pos[Floor][index_x] += player_speed;
}
