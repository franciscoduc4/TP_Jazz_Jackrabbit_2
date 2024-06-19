#include "player.h"

PlayerDTO::PlayerDTO(const uint8_t& playerId):
        GameElementDTO(ElementType::PLAYER),
        x(0),
        y(0),
        player_id(playerId),
        health(0),
        damage(0),
        speed(0),
        playerIsAlive(true),
        respawnTime(0),
        weapons(),
        currentWeapon(WeaponDTO(0, 0, 0, 0, 0)),
        type(CharacterType::INVALID),
        state(CharacterStateEntity::IDLE) {}

PlayerDTO::PlayerDTO(const uint32_t& x, const uint32_t& y, const uint8_t& player_id, uint8_t health, uint8_t damage, uint8_t speed,
                     const CharacterType& type, const CharacterStateEntity& state):
        GameElementDTO(ElementType::PLAYER),
        x(x),
        y(y),
        player_id(player_id),
        health(health),
        damage(damage),
        speed(speed),
        playerIsAlive(true),
        respawnTime(0),
        weapons(),
        currentWeapon(WeaponDTO(0, 0, 0, 0, 0)),
        type(type),
        state(state) {}


uint8_t PlayerDTO::getPlayerId() const { return player_id; }

uint32_t PlayerDTO::getX() const { return x; }

uint32_t PlayerDTO::getY() const { return y; }

uint8_t PlayerDTO::getDamage() const { return damage; }

uint8_t PlayerDTO::getHealth() const { return health; }

uint8_t PlayerDTO::getSpeed() const { return speed; }

WeaponDTO PlayerDTO::getCurrentWeapon() const { return currentWeapon; }

bool PlayerDTO::isAlive() const { return playerIsAlive; }

void PlayerDTO::setRespawnTime(int time) { respawnTime = time; }

uint8_t PlayerDTO::getRespawnTime() const { return respawnTime; }

CharacterType PlayerDTO::getType() const { return type; }

CharacterStateEntity PlayerDTO::getState() const { return state; }