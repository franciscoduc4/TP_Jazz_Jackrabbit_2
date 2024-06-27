#include "interface.h"
#include "../Common/Config/ClientConfig.h"
#include "../Common/printer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Interface::Interface() {
    this->font_path = ClientConfig::getInterfaceFontFile();    

    std::vector<std::string> letter{"X", "I", "D", ":", "A", "E", "F", "G", "H", "M", "N", "S"};
    int index_letter = 0;
    std::vector<std::vector<int>> font_sprites = ClientConfig::getInterfaceFontSprites();
    //Orden de digitos: 0 1 2 3 4 5 6 7 8 9 X I D : A E F G H M N S
    for (int i = 0; i < font_sprites.size(); i++) {
        if (i > 9) {
            this->index_letters[letter[index_letter]] = i;
            index_letter++;
        }
        this->numbers.push_back(RectangularSprite(font_sprites[i]));
    }
    
    this->draw_width = ClientConfig::getWidthFont();
    this->draw_height = ClientConfig::getHeightFont();
    this->counts = 0;
    this->x = 0;
    this->y = 0;

    std::vector<std::vector<int>> heart_sprites = ClientConfig::getInterfaceHeartSprites();
    for (int i = 0; i < heart_sprites.size(); i++) {
        this->hearts.push_back(RectangularSprite(heart_sprites[i]));
    }

    this->weapon_count = 0;
    std::vector<std::vector<int>> blaster_sprites = ClientConfig::getBlasterSprites();
    for (int i = 0; i < blaster_sprites.size(); i++) {
        this->weapons[WeaponType::BLASTER].push_back(RectangularSprite(blaster_sprites[i]));
    }
    std::vector<std::vector<int>> bouncer_sprites = ClientConfig::getBouncerSprites();
    for (int i = 0; i < bouncer_sprites.size(); i++) {
        this->weapons[WeaponType::BOUNCER].push_back(RectangularSprite(bouncer_sprites[i]));
    }
    std::vector<std::vector<int>> rfmissile_sprites = ClientConfig::getRfmissileSprites();
    for (int i = 0; i < rfmissile_sprites.size(); i++) {
        this->weapons[WeaponType::RFMISSILE].push_back(RectangularSprite(rfmissile_sprites[i]));
    }
    std::vector<std::vector<int>> frezzer_sprites = ClientConfig::getFrezzerSprites();
    for (int i = 0; i < frezzer_sprites.size(); i++) {
        this->weapons[WeaponType::FREEZER].push_back(RectangularSprite(frezzer_sprites[i]));
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

std::vector<RectangularSprite>::iterator Interface::weapon_sprite(WeaponType type) {
    std::vector<RectangularSprite>::iterator it = this->weapons[type].begin();
    for (int i = 0; i != this->weapon_count; i++) {
		++it;
		if (it == this->weapons[type].end()) {
			it = this->weapons[type].begin();
		}
	}
	this->weapon_count++;
    return it;
}


void Interface::draw_interface(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& iconTexture, std::unique_ptr<SDL2pp::Texture>& heartTexture, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players, PlayerDTO& mainPlayer, int lives, time_t time, WeaponType currentWeapon) {
    std::vector<RectangularSprite>::iterator it = icon_coords(mainPlayer.getCharacterType());
    std::string l = std::to_string(lives);
    std::string h = std::to_string(mainPlayer.getHealth());
    this->draw_width = window.GetWidth() / 40;
    this->draw_height = window.GetHeight() / 40;
    //int index_value_x = 10;
    
    //DRAW ICON
    renderer.Copy(iconTexture, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    
    //DRAW CANT LIVES
    renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters["X"]].getX(), this->numbers[this->index_letters["X"]].getY(), this->numbers[this->index_letters["X"]].getWidth(), this->numbers[this->index_letters["X"]].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
    x += this->draw_width * 2;
    std::string aux;
    for (int i = 0; i < l.size(); i++) {
        aux = l[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width * 2, this->draw_height * 2));
        x += this->draw_width * 2;
    }
    x += this->draw_width * 4;
    
    //DRAW POINTS
    draw_points(renderer, font, players);
    
    //DRAW TIME
    draw_time(window, renderer, font, time);
    
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

    //DRAW WEAPON
    int weapon_width = ClientConfig::getWeaponWidth();
    int weapon_height = ClientConfig::getWeaponHeight();
    x = window.GetWidth() - weapon_width;
    y = window.GetHeight() - weapon_height;
    std::vector<RectangularSprite>::iterator it_weapon = weapon_sprite(currentWeapon);
    renderer.Copy(*heartTexture, SDL2pp::Rect(it_weapon->getX(), it_weapon->getY(), it_weapon->getWidth(), it_weapon->getHeight()), SDL2pp::Rect(x, y, weapon_width, weapon_height));
        

    x = 0;
    y = 0;
}

std::map<uint8_t, int> Interface::sort_score(std::vector<PlayerDTO>& players) {
    std::map<uint8_t, int> scores;
    for (const auto& p : players) {
        scores[p.getPlayerId()] = p.getScore();
    }
    return scores;
}


void Interface::draw_points(SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& font, std::vector<PlayerDTO>& players) {
    std::map<uint8_t, int> players_scores = sort_score(players); 
    std::map<uint8_t, int>::iterator it_scores = players_scores.begin();
    std::vector<std::vector<int>>::iterator it_colors = this->colors.begin();
    int index_colors_r = 0;
    int index_colors_g = 1;
    int index_colors_b = 2;
    int index_default_color = 0;
    
    std::string playerId;
    std::string points;
    std::string aux;
    int initial_x = x;
    while (it_scores != players_scores.end()) {
        font->SetColorMod((*it_colors)[index_colors_r], (*it_colors)[index_colors_g], (*it_colors)[index_colors_b]);
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters["I"]].getX(), this->numbers[this->index_letters["I"]].getY(), this->numbers[this->index_letters["I"]].getWidth(), this->numbers[this->index_letters["I"]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters["D"]].getX(), this->numbers[this->index_letters["D"]].getY(), this->numbers[this->index_letters["D"]].getWidth(), this->numbers[this->index_letters["D"]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
        playerId = std::to_string(static_cast<int>(it_scores->first));
        for (int i = 0; i < playerId.size(); i++) {
            aux = playerId[i];
            renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
            x += this->draw_width;    
        }
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters[":"]].getX(), this->numbers[this->index_letters[":"]].getY(), this->numbers[this->index_letters[":"]].getWidth(), this->numbers[this->index_letters[":"]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width * 2;

        
        points = std::to_string(it_scores->second);
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

}

void Interface::draw_time(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& font, time_t time) {
    x = window.GetWidth() / 4 * 3; 
    y = 0;
    int index_colors_r = 0;
    int index_colors_g = 1;
    int index_colors_b = 2;
    int index_default_color = 0;
    
    int minutes = (time - time % 60) / 60; 
    int seconds = time % 60;
    std::string str_minutes = std::to_string(minutes).insert(0, 1, '0');
    std::string str_seconds = std::to_string(seconds);
    std::string aux;
    if (str_seconds.size() < 2) {
        str_seconds.insert(0, 1, '0');
    }
    int index_red_color = 1;
    if (minutes == 0 && seconds <= 10 && seconds % 2 == 1) {
        font->SetColorMod(this->colors[index_red_color][index_colors_r], this->colors[index_red_color][index_colors_g], this->colors[index_red_color][index_colors_b]);
    }
    
    for (int i = 0; i < str_minutes.size(); i++) {
        aux = str_minutes[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
    }
    renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters[":"]].getX(), this->numbers[this->index_letters[":"]].getY(), this->numbers[this->index_letters[":"]].getWidth(), this->numbers[this->index_letters[":"]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
    x += this->draw_width;
    for (int i = 0; i < str_seconds.size(); i++) {
        aux = str_seconds[i];
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[std::stoi(aux)].getX(), this->numbers[std::stoi(aux)].getY(), this->numbers[std::stoi(aux)].getWidth(), this->numbers[std::stoi(aux)].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height));
        x += this->draw_width;
    }
    font->SetColorMod(this->colors[index_default_color][index_colors_r], this->colors[index_default_color][index_colors_g], this->colors[index_default_color][index_colors_b]);

}


void Interface::draw_game_finished(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& background, std::unique_ptr<SDL2pp::Texture>& font) {
    renderer.Copy(background, SDL2pp::Rect(0, 0, 200, 100),
                      SDL2pp::Rect(0, 0, window.GetWidth(), window.GetHeight()));
    
    
    std::string text1 = "GAME";
    std::string text2 = "FINISHED";
    this->draw_width = window.GetWidth() / 15;
    x = this->draw_width;
    y = window.GetHeight() / 2;
    int index_colors_r = 0;
    int index_colors_g = 1;
    int index_colors_b = 2;
    int index_red_color = 1;
    font->SetColorMod(this->colors[index_red_color][index_colors_r], this->colors[index_red_color][index_colors_g], this->colors[index_red_color][index_colors_b]);
    std::string aux;
    for (int i = 0; i < text1.size(); i++) {
        aux = text1[i];        
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters[aux]].getX(), this->numbers[this->index_letters[aux]].getY(), this->numbers[this->index_letters[aux]].getWidth(), this->numbers[this->index_letters[aux]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height * 2));
        x += this->draw_width;
    }
    x += this->draw_width;
    
    for (int i = 0; i < text2.size(); i++) {
        aux = text2[i];        
        renderer.Copy(*font, SDL2pp::Rect(this->numbers[this->index_letters[aux]].getX(), this->numbers[this->index_letters[aux]].getY(), this->numbers[this->index_letters[aux]].getWidth(), this->numbers[this->index_letters[aux]].getHeight()), SDL2pp::Rect(x, y, this->draw_width, this->draw_height * 2));
        x += this->draw_width;
    }
}
