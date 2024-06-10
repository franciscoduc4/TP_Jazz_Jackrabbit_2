#include "interface.h"

#include <SDL2pp/SDL2pp.hh>

Interface::Interface(CharacterType character) {
    this->font_path = "../assets/Miscellaneous/Fonts.png";    
    this->numbers.push_back(RectangularSprite(215, 435, 50, 50));
    this->numbers.push_back(RectangularSprite(270, 435, 40, 50));
    this->numbers.push_back(RectangularSprite(335, 435, 55, 50));
    this->numbers.push_back(RectangularSprite(390, 435, 50, 50));
    this->numbers.push_back(RectangularSprite(455, 435, 50, 50));
    this->numbers.push_back(RectangularSprite(520, 435, 45, 50));
    this->numbers.push_back(RectangularSprite(575, 435, 50, 50));
    this->numbers.push_back(RectangularSprite(640, 435, 40, 50));
    this->numbers.push_back(RectangularSprite(700, 435, 45, 50));
    this->numbers.push_back(RectangularSprite(760, 435, 45, 50));
    this->numbers.push_back(RectangularSprite(285, 190, 25, 28)); //LETRA X
    
    this->draw_width = 15;
    this->draw_height = 15;
    this->counts = 0;

    switch (character) {
        case CharacterType::JAZZ:
            this->sprites.push_back(RectangularSprite(0, 3246, 40, 43));
            this->sprites.push_back(RectangularSprite(50, 3246, 42, 43));
            this->sprites.push_back(RectangularSprite(92, 3246, 40, 43));
            this->sprites.push_back(RectangularSprite(132, 3246, 40, 43));
            this->sprites.push_back(RectangularSprite(172, 3246, 40, 43));
            break;
        case CharacterType::LORI:
            this->sprites.push_back(RectangularSprite(0, 2906, 43, 49));
            this->sprites.push_back(RectangularSprite(43, 2906, 45, 49));
            this->sprites.push_back(RectangularSprite(88, 2906, 46, 49));
            this->sprites.push_back(RectangularSprite(134, 2906, 46, 49));
            this->sprites.push_back(RectangularSprite(180, 2906, 45, 49));
            this->sprites.push_back(RectangularSprite(225, 2906, 45, 49));
            break;
        default:
            this->sprites.push_back(RectangularSprite(0, 3202, 40, 42));
            this->sprites.push_back(RectangularSprite(40, 3202, 37, 42));
            this->sprites.push_back(RectangularSprite(77, 3202, 38, 42));
            this->sprites.push_back(RectangularSprite(115, 3202, 38, 42));
            this->sprites.push_back(RectangularSprite(153, 3202, 39, 42));
            this->sprites.push_back(RectangularSprite(192, 3202, 38, 42));
            this->sprites.push_back(RectangularSprite(230, 3202, 40, 42));
            this->sprites.push_back(RectangularSprite(270, 3202, 37, 42));
            this->sprites.push_back(RectangularSprite(307, 3202, 37, 42));
            this->sprites.push_back(RectangularSprite(344, 3202, 40, 42));
            break;
    }
    
}

std::string Interface::getFontPath() {
    return this->font_path;
}

std::vector<RectangularSprite>::iterator Interface::icon_coords() {
    std::vector<RectangularSprite>::iterator it = this->sprites.begin();
	for (int i = 0; i != this->counts; i++) {
		++it;
		if (it == this->sprites.end()) {
			it = this->sprites.begin();
		}
	}
	this->counts++;
    return it;
}



void Interface::draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, SDL2pp::Texture& font, int points, int lives) {
    std::vector<RectangularSprite>::iterator it = icon_coords();
    std::string p = std::to_string(points);
    std::string l = std::to_string(lives);
    int x = 0;
    int y = 0;
    this->draw_width = window.GetWidth() / 40;
    this->draw_height = window.GetHeight() / 40;
    int index_value_x = 10;
    renderer.Copy(iconTexture, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    renderer.Copy(font, SDL2pp::Rect(this->numbers[index_value_x].getX(), this->numbers[index_value_x].getY(), this->numbers[index_value_x].getWidth(), this->numbers[index_value_x].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    std::string aux;
    for (int i = 0; i < l.size(); i++) {
        aux = l[i];
        renderer.Copy(font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
        x += this->draw_width * 2;
    }
    x += this->draw_width * 4;

    for (int i = 0; i < p.size(); i++) {
        aux = p[i];
        renderer.Copy(font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
    }
}




