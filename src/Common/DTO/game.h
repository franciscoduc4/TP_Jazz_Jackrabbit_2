#ifndef GAMEDTO_H
#define GAMEDTO_H
#include <cstdint>
#include <string>
#include <vector>
#include "bullet.h"
#include "characterType.h"
#include "enemy.h"
#include "item.h"
#include "player.h"
#include "weapon.h"

class GameDTO : public CommandDTO {
    std::vector<PlayerDTO> players;
    std::vector<EnemyDTO> enemies;
    std::vector<BulletDTO> bullets;
    std::vector<ItemDTO> items;
    std::vector<WeaponDTO> weapons;
    std::vector<TileDTO> tiles;
};

#endif  // GAMEDTO_H
