#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "../../Common/sprite.h"
#include "../../Common/Types/character.h"
#include "../../Common/DTO/player.h"

#include <map>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>
#include <SDL2pp/SDL2pp.hh>

class Interface {
    std::string font_path;
    std::vector<RectangularSprite> numbers;
    std::map<std::string, int> index_letters;
    std::vector<RectangularSprite> hearts; 
    std::map<CharacterType, std::vector<RectangularSprite>> sprites;
    std::vector<std::vector<int>> colors;
    int x;
    int y;
    int draw_width;
    int draw_height;
    int counts;

public:
    Interface();

    std::string getFontPath();

    std::unique_ptr<SDL2pp::Texture> getFontTextures(SDL2pp::Renderer& renderer);

    std::vector<RectangularSprite>::iterator icon_coords(CharacterType type);

    void draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, std::unique_ptr<SDL2pp::Texture>& heartTexture, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players, PlayerDTO& mainPlayer, int lives, time_t time);

    std::map<uint8_t, int> sort_score(std::vector<PlayerDTO>& players);

    void draw_points(SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players);

    void draw_time(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& font, time_t time);

    void draw_game_finished(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, std::unique_ptr<SDL2pp::Texture>& font);
};

#endif