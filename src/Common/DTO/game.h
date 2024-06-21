#ifndef GAME_DTO_H
#define GAME_DTO_H
#include <cstdint>
#include <string>
#include <vector>

#include "../Types/dto.h"

#include "bullet.h"
#include "dto.h"
#include "enemy.h"
#include "item.h"
#include "player.h"
#include "tile.h"
#include "weapon.h"

class GameDTO: public DTO {
private:
    std::vector<PlayerDTO> players;
    std::vector<EnemyDTO> enemies;
    std::vector<BulletDTO> bullets;
    std::vector<ItemDTO> items;
    std::vector<WeaponDTO> weapons;
    std::vector<TileDTO> tiles;

    DTOType type = DTOType::GAME_DTO;

public:
    GameDTO() {}
    GameDTO(std::vector<PlayerDTO> players, std::vector<EnemyDTO> enemies,
            std::vector<BulletDTO> bullets, std::vector<ItemDTO> items,
            std::vector<WeaponDTO> weapons, std::vector<TileDTO> tiles);

    std::vector<PlayerDTO> getPlayers() const;

    std::vector<EnemyDTO> getEnemies() const;

    std::vector<BulletDTO> getBullets() const;

    std::vector<ItemDTO> getItems() const;

    std::vector<WeaponDTO> getWeapons() const;

    std::vector<TileDTO> getTiles() const;

    DTOType getType() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // GAME_DTO_H
