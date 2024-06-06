#include "points.h"
#include "../../Common/sprite.h"

#include <list>

#include <SDL2pp/SDL2pp.hh>

enum lvl { lvl1, lvl2 };
enum points { RedGem, GoldCoin, SilverCoin };

Points::Points(int level_type) {
    this->draw_width = 20;
    this->draw_height = 20;


    this->sprites[RedGem].push_back(RectangularSprite(145, 1240, 31, 30));
    this->sprites[RedGem].push_back(RectangularSprite(176, 1240, 29, 30));
    this->sprites[RedGem].push_back(RectangularSprite(205, 1240, 28, 30));
    this->sprites[RedGem].push_back(RectangularSprite(233, 1240, 29, 30));
    this->sprites[RedGem].push_back(RectangularSprite(262, 1240, 29, 30));
    this->sprites[RedGem].push_back(RectangularSprite(291, 1240, 29, 30));
    this->sprites[RedGem].push_back(RectangularSprite(320, 1240, 29, 30));
    this->sprites[RedGem].push_back(RectangularSprite(349, 1240, 30, 30));
    this->counts.push_back(0);
	

    this->sprites[GoldCoin].push_back(RectangularSprite(481, 1218, 27, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(508, 1218, 35, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(533, 1218, 23, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(556, 1218, 19, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(575, 1218, 15, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(590, 1218, 10, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(600, 1218, 15, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(615, 1218, 19, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(634, 1218, 24, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(658, 1218, 26, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(684, 1218, 26, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(710, 1218, 26, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(736, 1218, 24, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(760, 1218, 19, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(779, 1218, 15, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(794, 1218, 10, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(804, 1218, 14, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(818, 1218, 18, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(836, 1218, 23, 27));
    this->sprites[GoldCoin].push_back(RectangularSprite(859, 1218, 23, 27));
    this->counts.push_back(0);
	

    this->sprites[SilverCoin].push_back(RectangularSprite(482, 1266, 27, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(509, 1266, 33, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(532, 1266, 23, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(555, 1266, 18, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(573, 1266, 14, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(587, 1266, 10, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(597, 1266, 15, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(612, 1266, 19, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(631, 1266, 24, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(655, 1266, 26, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(681, 1266, 26, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(707, 1266, 27, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(734, 1266, 24, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(758, 1266, 19, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(777, 1266, 15, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(792, 1266, 10, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(802, 1266, 15, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(817, 1266, 19, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(836, 1266, 24, 26));
    this->sprites[SilverCoin].push_back(RectangularSprite(860, 1266, 15, 26));
	this->counts.push_back(0);
}


std::list<RectangularSprite>::iterator Points::actual_sprite_coord(int typepoint) {
    std::list<RectangularSprite>::iterator it = this->sprites[typepoint].begin();
    for (int i = 0; i < this->counts[typepoint]; i++) {
        ++it;
        if (it == this->sprites[typepoint].end()) {
            it = this->sprites[typepoint].begin();
        }
    }
    return it;
}

void Points::draw_points(SDL2pp::Renderer& renderer, SDL2pp::Texture& points, std::vector<ItemDTO> pointsdto) {
   	int index_x = 0;
   	int index_y = 1;
   	for (auto p : pointsdto) {
   		std::list<RectangularSprite>::iterator it = actual_sprite_coord(RedGem/*p.getType()*/);
        renderer.Copy(points, SDL2pp::Rect(it->getX(), it->getY(), it->getWidth(), it->getHeight()),
                      SDL2pp::Rect(p.getX(), p.getY(), this->draw_width, this->draw_height),
                      0.0, SDL2pp::NullOpt, 0);
        this->counts[RedGem/*p.getType()*/]++;
   	}
}

