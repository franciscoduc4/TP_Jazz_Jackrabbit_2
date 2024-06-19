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
    uint32_t x;
    uint32_t y;
    uint8_t player_id;
    uint8_t health;
    uint8_t damage;
    uint8_t speed;
    bool playerIsAlive;
    uint8_t respawnTime;
    std::map<uint8_t, WeaponDTO> weapons;
    WeaponDTO currentWeapon;
    CharacterType type;
    CharacterStateEntity state;

public:
    explicit PlayerDTO(const uint8_t& playerId);

    PlayerDTO(const uint32_t& x, const uint32_t& y, const uint8_t& player_id, uint8_t health, uint8_t damage, uint8_t speed,
              const CharacterType& type, const CharacterStateEntity& state);
    uint8_t getPlayerId() const;
    uint32_t getX() const;
    uint32_t getY() const;
    uint8_t getDamage() const;
    uint8_t getHealth() const;
    uint8_t getSpeed() const;
    WeaponDTO getCurrentWeapon() const;
    bool isAlive() const;
    void setRespawnTime(int time);
    uint8_t getRespawnTime() const;
    CharacterType getType() const;
    CharacterStateEntity getState() const;
};

#endif  // PLAYER_DTO_H_
