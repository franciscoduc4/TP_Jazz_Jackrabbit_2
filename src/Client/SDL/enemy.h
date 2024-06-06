#ifndef CLIENT_ENEMY_H_
#define CLIENT_ENEMY_H_

#include <list>
#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"
#include "../../Common/Types/enemy.h"
#include "../../Common/DTO/enemy.h"

#include "enemyweapon.h"

class Enemy {
    std::map<EnemyType, std::string> enemies_path;
    std::map<EnemyType, std::map<int, std::list<RectangularSprite>>> sprites;
    std::map<EnemyType, std::vector<int>> width_height;
    int count;
    int flip;
    

public:
    Enemy();

    std::string getPath(EnemyType enemy_type);

    std::list<RectangularSprite>::iterator enemy_img_coords(EnemyType enemy_type, int mov_type, int num_mov);

    void draw_enemy(SDL2pp::Window& window, SDL2pp::Renderer& renderer, SDL2pp::Texture& enemy, std::vector<EnemyDTO> enemies);
};

#endif  // CLIENT_ENEMY_H_
