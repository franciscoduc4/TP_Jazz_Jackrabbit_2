#ifndef PLAYER_DTO_H_
#define PLAYER_DTO_H_

#include <map>

#include "../../Common/sprite.h"
#include "../Types/character.h"
#include "../Types/entity.h"

#include "gameElement.h"
#include "weapon.h"

class PlayerDTO: public GameElementDTO {
private:
    uint8_t x;
    uint8_t y;
    uint8_t player_id;
    int health;
    int damage;
    int speed;
    bool playerIsAlive;
    int respawnTime;
    std::map<uint8_t, WeaponDTO> weapons;
    WeaponDTO currentWeapon;
    CharacterType type;
    CharacterStateEntity state;

public:
    explicit PlayerDTO(uint8_t playerId);

    PlayerDTO(uint8_t x, uint8_t y, uint8_t player_id, int health, int damage, int speed,
              CharacterType type, CharacterStateEntity state);
    uint8_t getPlayerId() const;
    uint8_t getX() const;
    uint8_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    WeaponDTO getCurrentWeapon() const;
    bool isAlive() const;
    void setRespawnTime(int time);
    int getRespawnTime() const;
    CharacterType getType() const;
    CharacterStateEntity getState() const;
};

#endif  // PLAYER_DTO_H_
