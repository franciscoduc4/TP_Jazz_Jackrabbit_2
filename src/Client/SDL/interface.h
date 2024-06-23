#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "../../Common/sprite.h"
#include "../../Common/Types/character.h"
#include "../../Common/DTO/player.h"

#include <map>
#include <string>
#include <memory>
#include <SDL2pp/SDL2pp.hh>

class Interface {
    std::string font_path;
    std::vector<RectangularSprite> numbers;
    std::vector<RectangularSprite> hearts; 
    std::map<CharacterType, std::vector<RectangularSprite>> sprites;
    std::vector<std::vector<int>> colors;
    int draw_width;
    int draw_height;
    int counts;

public:
    Interface();

    std::string getFontPath();

    std::unique_ptr<SDL2pp::Texture> getFontTextures(SDL2pp::Renderer& renderer);

    std::vector<RectangularSprite>::iterator icon_coords(CharacterType type);

    void draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, std::unique_ptr<SDL2pp::Texture>& heartTexture, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players, PlayerDTO& mainPlayer, int lives);

    std::map<int, uint8_t> sort_score(std::vector<PlayerDTO>& players);
};

#endif