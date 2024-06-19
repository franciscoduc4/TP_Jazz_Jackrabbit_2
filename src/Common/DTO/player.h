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
    explicit PlayerDTO(const uint8_t& playerId);

    PlayerDTO(const uint32_t& x, const uint32_t& y, const uint8_t& player_id, int health, int damage, int speed,
              const CharacterType& type, const CharacterStateEntity& state);
    uint8_t getPlayerId() const;
    uint32_t getX() const;
    uint32_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    WeaponDTO getCurrentWeapon() const;
    bool isAlive() const;
    void setRespawnTime(int time);
    int getRespawnTime() const;
    CharacterType getCharacterType() const;
    CharacterStateEntity getState() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // PLAYER_DTO_H_
