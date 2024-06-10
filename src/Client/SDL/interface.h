#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "../../Common/sprite.h"
#include "../../Common/Types/character.h"

#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>

class Interface {
    std::string font_path;
    std::vector<RectangularSprite> numbers; 
    std::vector<RectangularSprite> sprites;
    int draw_width;
    int draw_height;
    int counts;

public:
    explicit Interface(CharacterType character);

    std::string getFontPath();

    std::vector<RectangularSprite>::iterator icon_coords();

    void draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, SDL2pp::Texture& font, int points, int lives);

};

#endif