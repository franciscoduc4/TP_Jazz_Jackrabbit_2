#include "interface.h"
#include "../Common/Config/ClientConfig.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Interface::Interface() {
    this->font_path = ClientConfig::getInterfaceFontFile();    

    std::vector<std::vector<int>> font_sprites = ClientConfig::getInterfaceFontSprites();
    for (int i = 0; i < font_sprites.size(); i++) {
        //El ultimo es la letra X
        this->numbers.push_back(RectangularSprite(font_sprites[i]));
    }
    
    this->draw_width = ClientConfig::getWidthFont();
    this->draw_height = ClientConfig::getHeightFont();
    this->counts = 0;

    std::vector<std::vector<int>> jazz_icon_sprites = ClientConfig::getJazzIconSprites();
    for (int i = 0; i < jazz_icon_sprites.size(); i++) {
        this->sprites[CharacterType::JAZZ].push_back(RectangularSprite(jazz_icon_sprites[i]));
    }

    std::vector<std::vector<int>> lori_icon_sprites = ClientConfig::getLoriIconSprites();
    for (int i = 0; i < lori_icon_sprites.size(); i++) {
        this->sprites[CharacterType::LORI].push_back(RectangularSprite(lori_icon_sprites[i]));
    }

    std::vector<std::vector<int>> spaz_icon_sprites = ClientConfig::getSpazIconSprites();
    for (int i = 0; i < spaz_icon_sprites.size(); i++) {
        this->sprites[CharacterType::SPAZ].push_back(RectangularSprite(spaz_icon_sprites[i]));
    }
}

std::string Interface::getFontPath() {
    return this->font_path;
}

std::unique_ptr<SDL2pp::Texture> Interface::getFontTextures(SDL2pp::Renderer& renderer) {
    std::tuple<int, int, int> fontColorKey = ClientConfig::getInterfaceFontColourKey();
    SDL_Surface* font_surf = IMG_Load(getFontPath().c_str());
    SDL2pp::Surface fontSurface(font_surf);
    fontSurface.SetColorKey(true, SDL_MapRGB(fontSurface.Get()->format, std::get<0>(fontColorKey), std::get<1>(fontColorKey), std::get<2>(fontColorKey)));
    return std::make_unique<SDL2pp::Texture>(renderer, fontSurface);
}

std::vector<RectangularSprite>::iterator Interface::icon_coords(CharacterType type) {
    std::vector<RectangularSprite>::iterator it = this->sprites[type].begin();
	for (int i = 0; i != this->counts; i++) {
		++it;
		if (it == this->sprites[type].end()) {
			it = this->sprites[type].begin();
		}
	}
	this->counts++;
    return it;
}



void Interface::draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, CharacterType type, std::unique_ptr<SDL2pp::Texture>& font, int points, int lives) {
    std::vector<RectangularSprite>::iterator it = icon_coords(type);
    std::string p = std::to_string(points);
    std::string l = std::to_string(lives);
    int x = 0;
    int y = 0;
    this->draw_width = window.GetWidth() / 40;
    this->draw_height = window.GetHeight() / 40;
    int index_value_x = 10;
    renderer.Copy(iconTexture, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    renderer.Copy(*font, SDL2pp::Rect(this->numbers[index_value_x].getX(), this->numbers[index_value_x].getY(), this->numbers[index_value_x].getWidth(), this->numbers[index_value_x].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    std::string aux;
    for (int i = 0; i < l.size(); i++) {
        aux = l[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
        x += this->draw_width * 2;
    }
    x += this->draw_width * 4;

    for (int i = 0; i < p.size(); i++) {
        aux = p[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
    }
}




