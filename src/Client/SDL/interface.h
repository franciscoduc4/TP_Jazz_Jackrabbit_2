#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "../../Common/sprite.h"
#include "../../Common/Types/character.h"

#include <map>
#include <string>
#include <memory>
#include <SDL2pp/SDL2pp.hh>

class Interface {
    std::string font_path;
    std::vector<RectangularSprite> numbers;
    std::vector<RectangularSprite> hearts; 
    std::map<CharacterType, std::vector<RectangularSprite>> sprites;
    int draw_width;
    int draw_height;
    int counts;

public:
    Interface();

    std::string getFontPath();

    std::unique_ptr<SDL2pp::Texture> getFontTextures(SDL2pp::Renderer& renderer);

    std::vector<RectangularSprite>::iterator icon_coords(CharacterType type);

    void draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, std::unique_ptr<SDL2pp::Texture>& heartTexture, CharacterType type, std::unique_ptr<SDL2pp::Texture>& font, int points, int lives, int actual_health);

};

#endif