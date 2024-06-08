#include "deserializer.h"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "../Common/DTO/dto.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/queue.h"

#include "../../Common/DTO/player.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/Types/entity.h"


Deserializer::Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Deserializer::deserialize_msg(Command cmd, std::vector<char>& buffer) { 
    switch (cmd) {
        case Command::CREATE_GAME:
            break;
        case Command::GAMES_LIST:
            break;
        case Command::JOIN_GAME:
            break;
        case Command::GAME_MODE:
            receiveSnapshot(buffer);
            break;
    } 
}


void Deserializer::receiveSnapshot(std::vector<char>& buffer) {
    uint8_t i = 0;
    std::vector<PlayerDTO> players;
    uint8_t cant_jugadores = buffer[i];
    i++;
    uint8_t cant_player_atributos = 9; //sin contar currentWeapon
    uint8_t i_max = cant_jugadores * cant_player_atributos;
    while (i < i_max) {
        uint32_t playerId = static_cast<uint32_t>(buffer[i]);
        i++;
        int damage = static_cast<int>(buffer[i]);
        i++;
        int health = static_cast<int>(buffer[i]);
        i++;
        int speed = static_cast<int>(buffer[i]);
        i++;
        int getRespanwTime = static_cast<int>(buffer[i]);
        i++;
        uint16_t x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t y = static_cast<uint16_t>(buffer[i]);
        i++;
        CharacterType pj_type = static_cast<CharacterType>(buffer[i]);
        i++;
        CharacterStateEntity state = static_cast<CharacterStateEntity>(buffer[i]);
        i++;
        WeaponDTO weapon(0, 0, 0, 0, 0); //PRUEBA CON UN WEAPON CUALQUIERA
        PlayerDTO player(x, y, playerId, health, damage, speed, weapon, pj_type, state);
        players.push_back(player);
    }

    std::vector<EnemyDTO> enemies;
    uint8_t cant_enemies = buffer[i];
    i++;
    uint8_t cant_enemies_atributos = 8;
    i_max += cant_enemies * cant_enemies_atributos;
    while (i < i_max) {
        uint32_t enemyId = static_cast<uint32_t>(buffer[i]);
        i++;
        int enemy_damage = static_cast<int>(buffer[i]);
        i++;
        int enemy_health = static_cast<int>(buffer[i]);
        i++;
        int enemy_speed = static_cast<int>(buffer[i]);
        i++;
        uint16_t enemy_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t enemy_y = static_cast<uint16_t>(buffer[i]);
        i++;
        EnemyType enemy_type = static_cast<EnemyType>(buffer[i]);
        i++;
        EnemyStateEntity enemy_state = static_cast<EnemyStateEntity>(buffer[i]);
        i++;
        EnemyDTO enemy(enemy_x, enemy_y, enemyId, enemy_health, enemy_damage, enemy_speed, enemy_type, enemy_state);
        enemies.push_back(enemy);
    }
    
    std::vector<BulletDTO> bullets;
    uint8_t cant_bullets = buffer[i];
    i++;
    uint8_t cant_bullets_atributos = 6;
    i_max += cant_bullets * cant_bullets_atributos;
    while (i < i_max) {
        uint32_t bulletId = static_cast<uint32_t>(buffer[i]);
        i++;
        int bullet_damage = static_cast<int>(buffer[i]);
        i++;
        int bullet_speed = static_cast<int>(buffer[i]);
        i++;
        uint16_t bullet_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t bullet_y = static_cast<uint16_t>(buffer[i]);
        i++;
        int shooterId = static_cast<int>(buffer[i]);
        i++;
        BulletDTO bullet(bullet_x, bullet_y, bulletId, bullet_damage, bullet_speed, shooterId);
        bullets.push_back(bullet);
    }

    std::vector<ItemDTO> items;
    uint8_t cant_items = buffer[i];
    i++;
    uint8_t cant_items_atributos = 3;
    i_max += cant_items * cant_items_atributos;
    while (i < i_max) {
        uint16_t item_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t item_y = static_cast<uint16_t>(buffer[i]);
        i++;
        ItemType item_type = static_cast<ItemType>(buffer[i]);
        i++;
        ItemDTO item(item_x, item_y, item_type);
        items.push_back(item);
    }    

    std::vector<WeaponDTO> weapons;
    uint8_t cant_weapons = buffer[i];
    i++;
    uint8_t cant_weapons_atributos = 8 + cant_bullets_atributos;
    i_max += cant_weapons * cant_weapons_atributos;
    while (i < i_max) { 
        uint8_t weaponId = static_cast<uint8_t>(buffer[i]);
        i++;
        int weapon_damage = static_cast<int>(buffer[i]);
        i++;
        int weapon_ammo = static_cast<int>(buffer[i]);
        i++;
        int shoot_speed = static_cast<int>(buffer[i]);
        i++;
        uint16_t weapon_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t weapon_y = static_cast<uint16_t>(buffer[i]);
        i++;
        
        uint32_t bulletId = static_cast<uint32_t>(buffer[i]);
        i++;
        int bullet_damage = static_cast<int>(buffer[i]);
        i++;
        int bullet_speed = static_cast<int>(buffer[i]);
        i++;
        uint16_t bullet_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t bullet_y = static_cast<uint16_t>(buffer[i]);
        i++;
        int shooterId = static_cast<int>(buffer[i]);
        i++;
        

        WeaponDTO weapon(weaponId, weapon_x, weapon_y, weapon_damage, weapon_ammo);
        weapons.push_back(weapon);
    }

    
    std::vector<TileDTO> tiles;
    uint8_t cant_tiles = buffer[i];
    i++;
    uint8_t cant_tiles_atributos = 2;
    i_max += cant_tiles * cant_tiles_atributos;
    while (i < i_max) {
        uint16_t tile_x = static_cast<uint16_t>(buffer[i]);
        i++;
        uint16_t tile_y = static_cast<uint16_t>(buffer[i]);
        i++;
        TileDTO tile(tile_x, tile_y);
        tiles.push_back(tile);
    }

    //std::unique_ptr<DTO> game = std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles);
    queue->push(std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles));
    
} 