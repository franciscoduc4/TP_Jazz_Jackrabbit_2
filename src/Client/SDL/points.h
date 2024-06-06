#ifndef CLIENT_POINTS_H_
#define CLIENT_POINTS_H_

#include <list>
#include <map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"
#include "../../Common/DTO/item.h"

class Points {
    std::map<int, std::list<RectangularSprite>> sprites;
    std::vector<std::vector<int>> redgems;
    std::vector<std::vector<int>> goldcoin;
    std::vector<std::vector<int>> silvercoin;

    int cant_redgems;
    int cant_goldcoin;
    int cant_silvercoin;

    int draw_height;
    int draw_width;

    std::vector<int> counts;


public:
    Points(int level_type);

    void draw_points(SDL2pp::Renderer& renderer, SDL2pp::Texture& points, std::vector<ItemDTO> pointsdto);

    std::list<RectangularSprite>::iterator actual_sprite_coord(int typepoint);

};


#endif  // CLIENT_POINTS_H_
