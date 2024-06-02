#include "playerCharacter.h"

#include <utility>

#include "../../Common/Types/character.h"
#include "../../Common/Types/weapon.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/move.h"
#include "states/dead.h"
#include "states/idle.h"
#include "states/intoxicated.h"
#include "states/jazzSpecialAttack.h"
#include "states/jumping.h"
#include "states/shooting.h"
#include "states/spazSpecialAttack.h"

#include "gameMap.h"
#define CONFIG Configuration::getInstance()

Character::Character(GameMap& map, int16_t x, int16_t y, int16_t characterId, CharacterType type):
        map(map),
        x(0),
        y(0),
        characterId(0),
        health(100),
        initialHealth(100),
        dir(Move::RIGHT),
        maxMoves(5),
        timesRevived(0),
        maxRevived(3),
        currentWeapon(std::make_unique<Blaster>()),
        state(std::make_unique<IdleState>()) {}

int16_t Character::getX() { return x; }
int16_t Character::getY() { return y; }
int16_t Character::getId() { return characterId; }

void Character::recvDamage(uint16_t dmg, float time) {
    health -= dmg;
    if (health <= 0) {
        health = 0;
        die(time);
    } else {
        auto newState = std::unique_ptr<State>(state->receiveDamage(*this, dmg, time));
        if (newState) {
            state = std::move(newState);
        }
    }
    return;
}

void Character::setDir(Move dir) { this->dir = dir; }

void Character::update(float time) {
    auto newState = std::unique_ptr<State>(state->update(time));
    if (newState) {
        state = std::move(newState);
    }
    //currentWeapon->update(time);
}

void Character::shoot(float time) {
    auto newState = std::unique_ptr<State>(state->shoot(*this, std::move(currentWeapon), time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

void Character::moveRight(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Move::RIGHT, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

// void Character::sprintToRight(float time) {
//     // Sprint logic here
// }

void Character::moveLeft(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Move::LEFT, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

// void Character::sprintToLeft(float time) {
//     // Sprint logic here
// }

void Character::moveUp(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Move::UP, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

void Character::moveDown(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Move::DOWN, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

void Character::becomeIntoxicated(float duration) {
    // Intoxicated logic here
    return;
}

void Character::die(float respawnTime) {
    isDead = true;
    auto newState = std::unique_ptr<State>(state->die(*this, respawnTime));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::heal(uint16_t amount) {
    // Healing logic here
    return;
}

void Character::revive(float time) {
    if (maxRevived <= 0)
        return;
    timesRevived--;
    auto newState = std::unique_ptr<State>(state->revive(*this, time));
    if (newState) {
        state = std::move(newState);
    }
    health = initialHealth;
    isDead = false;
}

bool Character::isAlive() const { return !isDead; }

int16_t Character::getHealth() { return health; }
Move Character::getDir() { return dir; }
int16_t Character::getCharacterId() const { return characterId; }
float Character::getRespawnTime() const { return respawnTime; }
bool Character::characIsIntoxicated() { return isIntoxicated; }
float Character::getIntoxicatedTime() { return intoxicatedTime; }

void Character::moveRight() {
    int16_t newX = x + 1;
    if ((newX % maxMoves) != 0) {
        newX += 1;
        return;
    }
    int16_t newMapX = -1;
    map.moveObject(getPosition(), getMapPosition(), Move::RIGHT);
}

void Character::moveLeft() {
    int16_t newX = x - 1;
    if ((newX % maxMoves) != 0) {
        newX -= 1;
        return;
    }
    int16_t newMapX = -1;
    map.moveObject(getPosition(), getMapPosition(), Move::LEFT);
    if (newMapX >= 0) {
        x -= 1;
    }
}

void Character::moveUp() {
    int16_t newY = y - 1;
    if ((newY % maxMoves) != 0) {
        newY -= 1;
        return;
    }
    int16_t newMapY = -1;
    map.moveObject(getPosition(), getMapPosition(), Move::UP);
    if (newMapY >= 0) {
        y -= 1;
    }
}

void Character::moveDown() {
    int16_t newY = y + 1;
    if ((newY % maxMoves) != 0) {
        newY += 1;
        return;
    }
    int16_t newMapY = -1;
    map.moveObject(getPosition(), getMapPosition(), Move::DOWN);
    if (newMapY >= 0) {
        y += 1;
    }
}

int16_t Character::getX() { return x; }

int16_t Character::getY() { return y; }

int16_t Character::getId() { return characterId; }

int16_t Character::getMatrixX() { return x / maxMoves; }

int16_t Character::getMatrixY() { return y / maxMoves; }

std::vector<std::shared_ptr<Entity>> Character::getTargets() {
    std::vector<std::shared_ptr<Entity>> targets;
    map.getObjectsInShootRange({getMatrixX(), getMatrixY()}, direction);
    return targets;
}

Vector<int16_t> Character::getPosition() { return {x, y}; }

Vector<int16_t> Character::getMapPosition() { return {getMatrixX(), getMatrixY()}; }

void Character::setPosition(Vector<int16_t> newPosition) {
    x = newPosition.x;
    y = newPosition.y;
}

void Character::interact(Entity& other) {
    // Interaction logic here
    return;
}

void Character::switchWeapon(WeaponType type) {
    switch (type) {
        case WeaponType::BLASTER:
            currentWeapon = std::make_unique<Blaster>();
            break;
        case WeaponType::BOUNCER:
            currentWeapon = std::make_unique<Bouncer>();
            break;
        case WeaponType::FREEZER:
            currentWeapon = std::make_unique<Freezer>();
            break;
        case WeaponType::RFMISSILE:
            currentWeapon = std::make_unique<RFMissile>();
            break;
        default:
            currentWeapon = std::make_unique<Blaster>();
            return;
    }
}
