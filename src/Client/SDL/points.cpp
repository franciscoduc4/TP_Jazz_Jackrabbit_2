#include "points.h"
#include "../../Common/sprite.h"
#include "../../Common/Types/item.h"
#include "../Common/Config/ClientConfig.h"

#include <list>

#include <SDL2pp/SDL2pp.hh>

enum lvl { lvl1, lvl2 };

Points::Points(int level_type) {
    this->draw_width = 20;
    this->draw_height = 20;

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

void Points::draw_points(SDL2pp::Renderer& renderer, SDL2pp::Texture& points, std::vector<ItemDTO> pointsdto, PlayerDTO& player, int dir_x_screen, int dir_y_screen) {
   	int index_x = 0;
   	int index_y = 1;
   	int x;
    int y;
    int distance_main_item_x;
    int distance_main_item_y;
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
		
        renderer.Copy(points, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                      SDL2pp::Rect(x, y, this->draw_width, this->draw_height),
                      0.0, SDL2pp::NullOpt, 0);
        this->counts[static_cast<int>(p.getType())]++;
   	}
}

