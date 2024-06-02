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
#include "../../Common/Types/move.h"
#include "../../Common/Types/character.h"

#define CONFIG Configuration::getInstance()

Character::Character(GameMap& map, int16_t x, int16_t y, int16_t characterId, CharacterType type): 
    map(map), 
    x(0), 
    y(0), 
    characterId(0),
    health(100),
    initialHealth(100),
    dir(1),
    maxMoves(5),
    timesRevived(0),
    maxRevived(3) {}

int16_t Character::getX() { return x; }
int16_t Character::getY() { return y; }
int16_t Character::getId() { return characterId; }

void Character::recvDmg(uint16_t dmg, float time) {
    health -= dmg;
    if (health <= 0) {
        health = 0;
        die(time);
    } else {
        State *newState = state->receiveDamage(*this, dmg, time);
        if (newState != nullptr) {
            delete state;
            state = newState;
        }
    }
}
void Character::setDir(int16_t dir) { this->dir = dir; }

void Character::update(float time) {
    State* newState = state->update(time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
    currentWeapon->update(time);
}

void Character::shoot(float time) {
    State* newState = state->shoot(*this, currentWeapon, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }    
}

void Character::moveToRight(float time) {
    State* newState = state->move(*this, Move::RIGHT, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

void Character::sprintToRight(float time) {
}

void Character::moveToLeft(float time) {
    State* newState = state->move(*this, Move::LEFT, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

void Character::sprintToLeft(float time) {
}

void Character::moveToUp(float time) {
    State* newState = state->move(*this, Move::UP, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

void Character::moveToDown(float time){
    State* newState = state->move(*this, Move::DOWN, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

void Character::becomeIntoxicated(float duration) {
}

void Character::die(float respawnTime) {
    isDead = true;
    State* newState = state->die(*this, respawnTime);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

void Character::heal(uint16_t amount) {

}

void Character::revive(float time) {
    if (maxRevived <= 0) return;
    timesRevived--;
    State* newState = state->revive(*this, time);
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
    health = initialHealth;
    isDead = false;
}

bool Character::isAlive() const { return !isDead; }

int16_t Character::getHealth() const { return health; }
int16_t Character::getDir() const { return dir; }
int16_t Character::getCharacterId() const { return characterId; }
float Character::getRespawnTime() const { return respawnTime; }
bool Character::characIsIntoxicated() const { return isIntoxicated; }
float Character::getIntoxicatedTime() const { return intoxicatedTime; }

void Character::moveRight() {
    int16_t newX = x + 1;
    if ((newX % 32) != 0) {
        newX += 1;
        return;
    }
    int16_t newMapX =- 1;
    map.moveToRight(getMapX(), getMapY(), newMapX);
    if (newMapX >= 0){
        x += 1;
    }
}

void Character::moveLeft(){
    int16_t newX = x - 1;
    if ((newX % maxMoves) != 0) {
        newX -= 1;
        return;
    }
    int16_t newMapX =- 1;
    map.moveToLeft(getMapX(), getMapY(), newMapX);
    if (newMapX >= 0){
        x -= 1;
    }
}

void Character::moveUp(){
    int16_t newY = y - 1;
    if ((newY % maxMoves) != 0) {
        newY -= 1;
        return;
    }
    int16_t newMapY =- 1;
    map.moveToUp(getMapX(), getMapY(), newMapY);
    if (newMapY >= 0){
        y -= 1;
    }
}

void Character::moveDown(){
    int16_t newY = y + 1;
    if ((newY % maxMoves) != 0) {
        newY += 1;
        return;
    }
    int16_t newMapY =- 1;
    map.moveToDown(getMapX(), getMapY(), newMapY);
    if (newMapY >= 0){
        y += 1;
    }
}

int16_t Character::getX() {
    return x;
}
int16_t Character::getY() {
    return y;
}
int16_t Character::getId(){
    return characterId;
}
int16_t Character::getMapX(){
    return x / maxMoves;
}
int16_t Character::getMapY(){
    return y / maxMoves;
}
