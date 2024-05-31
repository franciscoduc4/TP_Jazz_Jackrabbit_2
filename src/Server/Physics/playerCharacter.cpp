#include "playerCharacter.h"
#include "config.h"
#include "states/idle.h"
#include "states/dead.h"
#include "states/intoxicated.h"
#include "states/jumping.h"
#include "states/running.h"
#include "states/shooting.h"
#include "states/loriSpecialAttack.h"
#include "states/jazzSpecialAttack.h"
#include "states/spazSpecialAttack.h"


#define CONFIG Configuration::getInstance()

Character::Character(GameMap& map, int16_t characterId, int16_t initialHealth)
    : map(map), characterId(characterId), health(initialHealth), x(0), y(0), dir(1),
      state(new IdleState()) {}

int16_t Character::getX() { return x; }
int16_t Character::getY() { return y; }
int16_t Character::getId() { return characterId; }

void Character::recvDmg(uint16_t dmg, float time) {
    state = std::unique_ptr<State>(state->receiveDamage(*this, dmg, time));
}

void Character::setDir(int16_t dir) { this->dir = dir; }

void Character::update(float time) {
    state = std::unique_ptr<State>(state->update(time));
    if (isDead) {
        respawnTime -= time;
        if (respawnTime <= 0) {
            isDead = false;
            health = CONFIG.getMaxHealth();  // Restablecer salud o según se necesite
            state = std::unique_ptr<State>(new IdleState());
        }
        return;
    }

    if (isIntoxicated) {
        intoxicatedTime -= time;
        if (intoxicatedTime <= 0) {
            isIntoxicated = false;
        }
    }

    if (shootCooldown > 0) {
        shootCooldown -= time;
    }
}

void Character::reload(float time) {
    state = std::unique_ptr<State>(state->reload(currentWeapon.get(), time));
}

void Character::shoot(float time) {
    state = std::unique_ptr<State>(state->shoot(*this, currentWeapon.get(), time));
}

void Character::moveToRight(float time) {
    state = std::unique_ptr<State>(state->move(*this, 1, time));
}

void Character::sprintToRight(float time) {
    x += sprintSpeed * time;
}

void Character::moveToLeft(float time) {
    state = std::unique_ptr<State>(state->move(*this, -1, time));
}

void Character::sprintToLeft(float time) {
    x -= sprintSpeed * time;
}

void Character::jump(float time) {
    state = std::unique_ptr<State>(state->jump(*this, time));
}

void Character::becomeIntoxicated(float duration) {
    state = std::unique_ptr<State>(state->becomeIntoxicated(*this, duration));
}

void Character::die(float respawnTime) {
    state = std::unique_ptr<State>(state->die(*this, respawnTime));
}

void Character::heal(uint16_t amount) {
    if (!isDead) {
        health += amount;
        if (health > CONFIG.getMaxHealth()) {  
            health = CONFIG.getMaxHealth();
        }
    }
}

bool Character::isAlive() const { return !isDead; }

int16_t Character::getHealth() const { return health; }
int16_t Character::getDir() const { return dir; }
int16_t Character::getCharacterId() const { return characterId; }
float Character::getRespawnTime() const { return respawnTime; }
bool Character::isIntoxicated() const { return isIntoxicated; }
float Character::getIntoxicatedTime() const { return intoxicatedTime; }

Character::~Character() {}
