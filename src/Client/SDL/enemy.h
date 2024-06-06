#ifndef CLIENT_ENEMY_H_
#define CLIENT_ENEMY_H_

#include <list>
#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"

#include "enemyweapon.h"

class Enemy {
    std::string path;
    std::map<int, std::list<RectangularSprite>> sprites;
    EnemyWeapon weapon;
    int count;
    int pos_x;
    int pos_y;
    int draw_width;
    int draw_height;
    int flip;
    int speed;


public:
    Enemy(int enemy, int x, int y);

    std::string getPath();

    std::list<RectangularSprite>::iterator enemy_img_coords(int mov_type, int num_mov);

    void draw_enemy(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy,
                    int mov_type, int x_screen, int y_screen);
};

#endif  // CLIENT_ENEMY_H_
