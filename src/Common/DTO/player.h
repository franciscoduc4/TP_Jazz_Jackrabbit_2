#ifndef PLAYER_DTO_H_
#define PLAYER_DTO_H_

#include <map>

#include "../../Common/sprite.h"

#include "gameElement.h"
#include "weapon.h"

class PlayerDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    uint32_t player_id;
    int health;
    int damage;
    int speed;
    bool playerIsAlive;
    int respawnTime;
    std::map<uint8_t, WeaponDTO> weapons;
    WeaponDTO currentWeapon;

public:
    PlayerDTO(uint16_t x, uint16_t y, uint32_t player_id, int health, int damage, int speed, WeaponDTO currentWeapon);
    uint32_t getPlayerId() const;
    uint16_t getX() const;
    uint16_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    WeaponDTO getCurrentWeapon() const;
    bool isAlive() const;
    void setRespawnTime(int time);
    int getRespawnTime() const;
};

#endif  // PLAYER_DTO_H_
