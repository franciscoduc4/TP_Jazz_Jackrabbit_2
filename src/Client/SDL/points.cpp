#include "points.h"
#include "../../Common/sprite.h"
#include "../../Common/Types/item.h"
#include "../Common/Config/ClientConfig.h"

#include <list>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Points::Points() {
    this->draw_width = ClientConfig::getItemsWidth();
    this->draw_height = ClientConfig::getItemsHeight();

    std::vector<std::vector<int>> redgems_sprites = ClientConfig::getRedGemSprites();    
    for (int i = 0; i < redgems_sprites.size(); i++) {
        this->sprites[ItemType::GEM].push_back(RectangularSprite(redgems_sprites[i]));
    }
    this->counts.push_back(0);

    std::vector<std::vector<int>> goldcoin_sprites = ClientConfig::getGoldCoinSprites();
    for (int i = 0; i < goldcoin_sprites.size(); i++) {
        this->sprites[ItemType::GOLD_COIN].push_back(RectangularSprite(goldcoin_sprites[i]));
    }
    this->counts.push_back(0);

    std::vector<std::vector<int>> silvercoin_sprites = ClientConfig::getSilverCoinSprites();
    for (int i = 0; i < silvercoin_sprites.size(); i++) {
        this->sprites[ItemType::SILVER_COIN].push_back(RectangularSprite(silvercoin_sprites[i]));
    }
    this->counts.push_back(0);

}


std::unique_ptr<SDL2pp::Texture> Points::getItemsTextures(SDL2pp::Renderer& renderer) {
    SDL_Surface* items_surf = IMG_Load("../assets/Miscellaneous/Items&Objects.png");
    SDL2pp::Surface itemsSurface(items_surf);
    itemsSurface.SetColorKey(true, SDL_MapRGB(itemsSurface.Get()->format, 0, 128, 255));
    return std::make_unique<SDL2pp::Texture>(renderer, itemsSurface);
}

std::list<RectangularSprite>::iterator Points::actual_sprite_coord(ItemType typepoint) {
    std::list<RectangularSprite>::iterator it = this->sprites[typepoint].begin();
    for (int i = 0; i < this->counts[static_cast<int>(typepoint)]; i++) {
        ++it;
        if (it == this->sprites[typepoint].end()) {
            it = this->sprites[typepoint].begin();
        }
    }
    return it;
}

void Points::draw_points(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::unique_ptr<SDL2pp::Texture>& points, std::vector<ItemDTO> pointsdto, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
   	int index_x = 0;
   	int index_y = 1;
   	uint32_t x;
    uint32_t y;
    int distance_main_item_x = 0;
    int distance_main_item_y = 0;
    int i = 0;
    for (auto p : pointsdto) {
   		std::list<RectangularSprite>::iterator it = actual_sprite_coord(p.getType());
        x = p.getX();
		y = p.getY();
		
        if (dir_x_screen != 0) { 
            distance_main_item_x = x - player.getX();
            x = dir_x_screen + distance_main_item_x;
        }
        if (dir_y_screen != 0) {
            distance_main_item_y = y - player.getX();
            y = dir_y_screen + distance_main_item_y;
        }
		
        if (abs(distance_main_item_x) <= window.GetWidth() && abs(distance_main_item_y) <= window.GetHeight()) {
            renderer.Copy(*points, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                      SDL2pp::Rect(x, y, this->draw_width, this->draw_height),
                      0.0, SDL2pp::NullOpt, 0);
        }
        this->counts[static_cast<int>(p.getType())]++;
        i++;
   	}
}

