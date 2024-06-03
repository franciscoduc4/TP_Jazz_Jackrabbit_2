#include "game.h"

GameDTO::GameDTO(std::vector<PlayerDTO> players, std::vector<EnemyDTO> enemies,
                 std::vector<BulletDTO> bullets, std::vector<ItemDTO> items,
                 std::vector<WeaponDTO> weapons, std::vector<TileDTO> tiles):
        players(players),
        enemies(enemies),
        bullets(bullets),
        items(items),
        weapons(weapons),
        tiles(tiles) {}


std::vector<PlayerDTO> GameDTO::getPlayers() const { return players; }

std::vector<EnemyDTO> GameDTO::getEnemies() const { return enemies; }

std::vector<BulletDTO> GameDTO::getBullets() const { return bullets; }

std::vector<ItemDTO> GameDTO::getItems() const { return items; }

std::vector<WeaponDTO> GameDTO::getWeapons() const { return weapons; }

std::vector<TileDTO> GameDTO::getTiles() const { return tiles; }

DTOType GameDTO::getType() const { return type; }
