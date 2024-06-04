#include "playerCharacter.h"

#include <utility>

#include "../../Common/Config/ServerConfig.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/weapon.h"
#include "states/dead.h"
#include "states/idle.h"
#include "states/intoxicated.h"
#include "states/jumping.h"
#include "states/shooting.h"
#include "states/specialAttack.h"

#include "gameMap.h"
#define CONFIG ServerConfig::getInstance()

Character::Character(GameMap& map, int16_t x, int16_t y, int16_t characterId, CharacterType type):
        map(map),
        x(CONFIG->getCharacterInitialX()),
        y(CONFIG->getCharacterInitialY()),
        characterId(0),
        health(CONFIG->getCharacterInitialHealth()),
        initialHealth(CONFIG->getCharacterInitialHealth()),
        dir(Direction::RIGHT),
        maxMoves(CONFIG->getCharacterMaxMoves()),
        timesRevived(0),
        maxRevived(CONFIG->getCharacterMaxRevived()),
        currentWeapon(std::make_unique<Blaster>()),
        state(std::make_unique<IdleState>()) {}

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

void Character::setDir(Direction dir) { this->dir = dir; }

void Character::update(float time) {
    auto newState = std::unique_ptr<State>(state->exec(*this, time));
    if (newState) {
        state = std::move(newState);
    }
    // currentWeapon->update(time);
}

void Character::shoot(float time) {
    auto newState = std::unique_ptr<State>(state->shoot(*this, std::move(currentWeapon), time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

void Character::moveRight(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::RIGHT, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

// void Character::sprintToRight(float time) {
//     // Sprint logic here
// }

void Character::moveLeft(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::LEFT, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

// void Character::sprintToLeft(float time) {
//     // Sprint logic here
// }

void Character::moveUp(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::UP, time));
    if (newState) {
        state = std::move(newState);
    }
    return;
}

void Character::moveDown(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::DOWN, time));
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

int16_t Character::getCharacterId() const { return characterId; }
float Character::getRespawnTime() const { return respawnTime; }

void Character::moveRight() {
    auto position = getPosition();
    auto mapPosition = getMapPosition();
    map.moveObject(position, mapPosition, Direction::RIGHT);
}

void Character::moveLeft() {
    auto position = getPosition();
    auto mapPosition = getMapPosition();
    map.moveObject(position, mapPosition, Direction::LEFT);
}

void Character::moveUp() {
    auto position = getPosition();
    auto mapPosition = getMapPosition();
    map.moveObject(position, mapPosition, Direction::UP);
}

void Character::moveDown() {
    auto position = getPosition();
    auto mapPosition = getMapPosition();
    map.moveObject(position, mapPosition, Direction::DOWN);
}


std::vector<std::shared_ptr<Entity>> Character::getTargets() {
    std::vector<std::shared_ptr<Entity>> targets;
    map.getObjectsInShootRange({getMatrixX(), getMatrixY()}, direction);
    return targets;
}

Vector<int16_t> Character::getPosition() { return {x, y}; }

Vector<int16_t> Character::getMapPosition() { return {getMatrixX(), getMatrixY()}; }

// void Character::setPosition(Vector<int16_t> newPosition) {
//     x = newPosition.x;
//     y = newPosition.y;
// }

void Character::interact(std::shared_ptr<Entity>& other) {
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


int16_t Character::getHealth() const { return health; }
Direction Character::getDir() const { return dir; }
int16_t Character::getX() const { return x; }
int16_t Character::getMatrixX() const { return x / maxMoves; }
int16_t Character::getMatrixY() const { return y / maxMoves; }
int16_t Character::getY() const { return y; }
bool Character::characIsIntoxicated() const { return isIntoxicated; }
float Character::getIntoxicatedTime() const { return intoxicatedTime; }
