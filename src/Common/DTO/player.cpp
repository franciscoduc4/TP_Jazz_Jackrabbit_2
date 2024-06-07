#include "player.h"

PlayerDTO::PlayerDTO(uint16_t x, uint16_t y, uint32_t playerId, int health, int damage, int speed, WeaponDTO currentWeapon, CharacterType type):
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
        type(type) {}


uint32_t PlayerDTO::getPlayerId() const { return player_id; }

uint16_t PlayerDTO::getX() const { return x; }

uint16_t PlayerDTO::getY() const { return y; }

int PlayerDTO::getDamage() const { return damage; }

int PlayerDTO::getHealth() const { return health; }

int PlayerDTO::getSpeed() const { return speed; }

WeaponDTO PlayerDTO::getCurrentWeapon() const { return currentWeapon; }

bool PlayerDTO::isAlive() const { return playerIsAlive; }

void PlayerDTO::setRespawnTime(int time) { respawnTime = time; }

int PlayerDTO::getRespawnTime() const { return respawnTime; }

CharacterType PlayerDTO::getType() const { return type; }