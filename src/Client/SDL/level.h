#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <vector>

#include "../../Common/DTO/player.h"

class Level {
    std::map<int, std::string> paths;
    std::map<int, std::vector<int>> pixels_pos;
    int max_pixel_x_floor;
    int floor_height;
    int background_width;
    int background_height;

public:
    explicit Level(int level);

    std::string getLevelPath(int type);

    std::vector<int> draw_background(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, PlayerDTO& player);

    void draw_floor(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& floor, int player_speed);

};
#endif //LEVEL_H