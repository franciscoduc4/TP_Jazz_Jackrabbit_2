#ifndef GAME_DTO_H
#define GAME_DTO_H
#include <cstdint>
#include <string>
#include <vector>

#include "bullet.h"
#include "characterType.h"
#include "enemy.h"
#include "item.h"
#include "player.h"
#include "tile.h"
#include "weapon.h"

class GameDTO {
private:
    std::vector<PlayerDTO> players;
    std::vector<EnemyDTO> enemies;
    std::vector<BulletDTO> bullets;
    std::vector<ItemDTO> items;
    std::vector<WeaponDTO> weapons;
    std::vector<TileDTO> tiles;
public:
    GameDTO(std::vector<PlayerDTO> players, std::vector<EnemyDTO> enemies,
            std::vector<BulletDTO> bullets, std::vector<ItemDTO> items,
            std::vector<WeaponDTO> weapons, std::vector<TileDTO> tiles);

    std::vector<PlayerDTO> getPlayers() const;

    std::vector<EnemyDTO> getEnemies() const;

    std::vector<BulletDTO> getBullets() const;

    std::vector<ItemDTO> getItems() const;

    std::vector<WeaponDTO> getWeapons() const;

    std::vector<TileDTO> getTiles() const;
};

#endif  // GAME_DTO_H
