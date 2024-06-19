#include "player.h"

PlayerDTO::PlayerDTO(uint8_t playerId):
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

PlayerDTO::PlayerDTO(uint32_t x, uint32_t y, uint8_t playerId, int health, int damage, int speed,
                     CharacterType type, CharacterStateEntity state):
        x(x),
        y(y),
        player_id(playerId),
        health(health),
        damage(damage),
        speed(speed),
        playerIsAlive(true),
        respawnTime(0),
        weapons(),
        currentWeapon(currentWeapon),
        type(type),
        state(state) {}


uint8_t PlayerDTO::getPlayerId() const { return player_id; }

uint32_t PlayerDTO::getX() const { return x; }

uint32_t PlayerDTO::getY() const { return y; }

int PlayerDTO::getDamage() const { return damage; }

int PlayerDTO::getHealth() const { return health; }

int PlayerDTO::getSpeed() const { return speed; }

WeaponDTO PlayerDTO::getCurrentWeapon() const { return currentWeapon; }

bool PlayerDTO::isAlive() const { return playerIsAlive; }

void PlayerDTO::setRespawnTime(int time) { respawnTime = time; }

int PlayerDTO::getRespawnTime() const { return respawnTime; }

CharacterType PlayerDTO::getType() const { return type; }

CharacterStateEntity PlayerDTO::getState() const { return state; }