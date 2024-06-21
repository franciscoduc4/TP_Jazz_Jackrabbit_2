#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <vector>

#include "../../Common/DTO/player.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/Types/tile.h"

class Level {
    std::map<TileType, std::string> paths;
    std::map<TileType, std::vector<int>> pixels_pos;
    std::map<TileType, std::vector<int>> width_height;
    int max_pixel_x_floor;
    int floor_height;
    int background_width;
    int background_height;

public:
    explicit Level(uint8_t level);

    std::map<TileType, std::unique_ptr<SDL2pp::Texture>> getTilesTextures(SDL2pp::Renderer& renderer);

    std::string getLevelPath(TileType type);

    std::vector<int> draw_background(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& textures, PlayerDTO& player);

    void draw_floor(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& textures, int player_speed);

    void draw_tiles(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<TileType, std::unique_ptr<SDL2pp::Texture>>& tiles_textures, std::vector<TileDTO>& tiles);

};
#endif //LEVEL_H