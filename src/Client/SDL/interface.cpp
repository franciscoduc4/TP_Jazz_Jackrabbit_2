#include "interface.h"
#include "../Common/Config/ClientConfig.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Interface::Interface() {
    this->font_path = ClientConfig::getInterfaceFontFile();    

    std::vector<std::vector<int>> font_sprites = ClientConfig::getInterfaceFontSprites();
    //Orden de digitos: 0 1 2 3 4 5 6 7 8 9 X I D :
    for (int i = 0; i < font_sprites.size(); i++) {
        this->numbers.push_back(RectangularSprite(font_sprites[i]));
    }
    
    this->draw_width = ClientConfig::getWidthFont();
    this->draw_height = ClientConfig::getHeightFont();
    this->counts = 0;

    std::vector<std::vector<int>> heart_sprites = ClientConfig::getInterfaceHeartSprites();
    for (int i = 0; i < heart_sprites.size(); i++) {
        this->hearts.push_back(RectangularSprite(heart_sprites[i]));
    }

    this->colors = ClientConfig::getInterfaceColors();


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


void Interface::draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, std::unique_ptr<SDL2pp::Texture>& heartTexture, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players, PlayerDTO& mainPlayer, int lives) {
    std::vector<RectangularSprite>::iterator it = icon_coords(mainPlayer.getCharacterType());
    std::string l = std::to_string(lives);
    std::string h = std::to_string(mainPlayer.getHealth());
    int x = 0;
    int y = 0;
    this->draw_width = window.GetWidth() / 40;
    this->draw_height = window.GetHeight() / 40;
    int index_value_x = 10;
    int index_value_i = 11;
    int index_value_d = 12;
    int index_value_dos_puntos = 13;

    //DRAW ICON
    renderer.Copy(iconTexture, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    
    //DRAW CANT LIVES
    renderer.Copy(*font, SDL2pp::Rect(this->numbers[index_value_x].getX(), this->numbers[index_value_x].getY(), this->numbers[index_value_x].getWidth(), this->numbers[index_value_x].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    std::string aux;
    for (int i = 0; i < l.size(); i++) {
        aux = l[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
        x += this->draw_width * 2;
    }
    x += this->draw_width * 4;
    
    //DRAW POINTS
    std::map<int, uint8_t> players_scores = sort_score(players); 
    std::map<int, uint8_t>::reverse_iterator it_scores = players_scores.rbegin();
    std::vector<std::vector<int>>::iterator it_colors = this->colors.begin();
    int index_colors_r = 0;
    int index_colors_g = 1;
    int index_colors_b = 2;
    int index_default_color = 0;
    std::string playerId;
    std::string points;
    int initial_x = x;
    while (it_scores != players_scores.rend()) {
        font->SetColorMod((*it_colors)[index_colors_r], (*it_colors)[index_colors_g], (*it_colors)[index_colors_b]);
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[index_value_i].getX(), this->numbers[index_value_i].getY(), this->numbers[index_value_i].getWidth(), this->numbers[index_value_i].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[index_value_d].getX(), this->numbers[index_value_d].getY(), this->numbers[index_value_d].getWidth(), this->numbers[index_value_d].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
        playerId = std::to_string(static_cast<int>(it_scores->second));
        for (int i = 0; i < playerId.size(); i++) {
            aux = playerId[i];
            renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
            x += this->draw_width;    
        }
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[index_value_dos_puntos].getX(), this->numbers[index_value_dos_puntos].getY(), this->numbers[index_value_dos_puntos].getWidth(), this->numbers[index_value_dos_puntos].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width * 2;

        
        points = std::to_string(it_scores->first);
        for (int i = 0; i < points.size(); i++) {
            aux = points[i];
            renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
            x += this->draw_width;  
        }
        y += this->draw_height;
        x = initial_x;
        it_scores++;
        it_colors++;
        if (it_colors == this->colors.end()) {
            it_colors = this->colors.begin();
        }
    }
    font->SetColorMod(this->colors[index_default_color][index_colors_r], this->colors[index_default_color][index_colors_g], this->colors[index_default_color][index_colors_b]);
    
    //DRAW HEALTH    
    this->draw_height = window.GetHeight() / 30;
    x = 0;
    y = window.GetHeight() - this->draw_height;
    for (int i = 0; i < h.size(); i++) {
        aux = h[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
    }
    int cant_hearts = mainPlayer.getHealth() / 10;
    int index_hearts = 0;
    for (int i = 0; i < cant_hearts; i++) {
        renderer.Copy(*heartTexture, SDL2pp::Rect(this->hearts[index_hearts].getX(), this->hearts[index_hearts].getY(), this->hearts[index_hearts].getWidth(), this->hearts[index_hearts].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        if (index_hearts == 0) {
            index_hearts++;
        } else {
            index_hearts--;
        }
        x += this->draw_width;
    }
}

std::map<int, uint8_t> Interface::sort_score(std::vector<PlayerDTO>& players) {
    std::map<int, uint8_t> scores;
    for (auto p : players) {
        scores[p.getScore()] = p.getPlayerId();
    }
    //scores[2000/*p.getPoints()*/] = 1;
    //scores[3000] = 2;
    //scores[800] = 3;
    return scores;
}
