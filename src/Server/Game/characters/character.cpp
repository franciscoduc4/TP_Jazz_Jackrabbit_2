#include "character.h"

#include "../gameMap.h"

#define CONFIG ServerConfig::getInstance()

Character::Character(GameMap& gameMap, Vector<int16_t> pos, int16_t characterId, CharacterType type,
                     float horizontalSpeed, float sprintSpeed, float verticalSpeed,
                     float jumpHeight, float shootCooldownTime):
        Entity(pos, characterId, CONFIG->getCharacterInitialHealth(), Direction::RIGHT),
        type(type),
        gameMap(gameMap),
        maxHealth(CONFIG->getCharacterInitialHealth()),
        reviveTime(CONFIG->getCharacterReviveTime()),
        maxRevived(CONFIG->getCharacterMaxRevived()),
        movesPerCell(CONFIG->getCharacterMaxMovesPerCell()),
        timesRevived(0),
        respawnTime(CONFIG->getCharacterRespawnTime()),
        damageTime(CONFIG->getCharacterDamageTime()),
        intoxicatedTime(CONFIG->getCharacterIntoxicatedTime()),
        horizontalSpeed(horizontalSpeed),
        sprintSpeed(sprintSpeed),
        verticalSpeed(verticalSpeed),
        jumpHeight(jumpHeight),
        shootCooldownTime(shootCooldownTime),
        currentWeapon(std::make_unique<Blaster>()),
        state(std::make_unique<IdleState>()) {}

void Character::recvDamage(uint16_t dmg, float time) {
    Entity::recvDamage(dmg, time);
    if (isDead) {
        return;
    }
    auto newState = std::unique_ptr<State>(state->receiveDamage(*this, dmg, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::update(float time) {
    auto newState = std::unique_ptr<State>(state->exec(*this, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::shoot(float time) {
    auto newState = std::unique_ptr<State>(state->shoot(*this, std::move(currentWeapon), time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveRight(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::RIGHT, time));
    if (newState) {
        state = std::move(newState);
    }
}

// void Character::sprintRight(float time) {
//     // Sprint logic here
// }

void Character::moveLeft(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::LEFT, time));
    if (newState) {
        state = std::move(newState);
    }
}

// void Character::sprintLeft(float time) {
//     // Sprint logic here
// }

void Character::moveUp(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::UP, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveDown(float time) {
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::DOWN, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::becomeIntoxicated(float duration) {
    isIntoxicated = true;
    intoxicatedTime = duration;
}

void Character::die(float respawnTime) {
    isDead = true;
    auto newState = std::unique_ptr<State>(state->die(*this, respawnTime));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::heal(int32_t healQnt) {
    Entity::heal(healQnt);
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

std::vector<std::shared_ptr<Entity>> Character::getTargets() {
    std::vector<std::shared_ptr<Entity>> targets;
    // map.getObjectsInShootRange({pos.x / maxMoves, pos.y / maxMoves}, dir);
    return targets;
}

void Character::interact(std::shared_ptr<Entity>& other) {
    // Interaction logic here
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

WeaponType Character::getCurrentWeaponType() {
    return currentWeapon->getWeaponType();
}


void Character::moveRight() {
    auto mapPosition = getMapPosition(movesPerCell);
    gameMap.moveObject(pos, mapPosition, Direction::RIGHT);
}

void Character::moveLeft() {
    auto mapPosition = getMapPosition(movesPerCell);
    gameMap.moveObject(pos, mapPosition, Direction::LEFT);
}

void Character::moveUp() {
    auto mapPosition = getMapPosition(movesPerCell);
    gameMap.moveObject(pos, mapPosition, Direction::UP);
}

void Character::moveDown() {
    auto mapPosition = getMapPosition(movesPerCell);
    gameMap.moveObject(pos, mapPosition, Direction::DOWN);
}

bool Character::characIsIntoxicated() const { return isIntoxicated; }

float Character::getIntoxicatedTime() const { return intoxicatedTime; }

CharacterType Character::getCharacterType() { return type; }
