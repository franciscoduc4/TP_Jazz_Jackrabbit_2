#include <list>
#include <map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"

class Points {
    std::map<int, std::list<Sprite>> sprites;
    std::vector<std::vector<int>> redgems;
    std::vector<std::vector<int>> goldcoin;
    std::vector<std::vector<int>> silvercoin;

    int cant_redgems;
    int cant_goldcoin;
    int cant_silvercoin;

    int draw_width;
    int draw_height;

    std::vector<int> counts;


public:
    Points(int level_type);

    void draw_points(SDL2pp::Renderer& renderer, SDL2pp::Texture& points);

    std::list<Sprite>::iterator actual_sprite_coord(int typepoint);

    void verify_point_obtained(SDL2pp::Rect& player_rect);
};
