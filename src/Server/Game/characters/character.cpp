#include "character.h"

#include "../gameMap.h"

#define CONFIG ServerConfig::getInstance()

Character::Character(GameMap& gameMap, Vector<uint8_t> pos, uint8_t playerId, CharacterType type,
                     float horizontalSpeed, float sprintSpeed, float verticalSpeed,
                     float jumpHeight, float shootCooldownTime):
        Entity(pos, playerId, CONFIG->getCharacterInitialHealth(), Direction::RIGHT,
               EntityType::CHARACTER),
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
        state(std::make_unique<IdleState>()) {
    std::cout << "[CHARACTER] Character created with ID: " << static_cast<int>(playerId)
              << std::endl;
}

void Character::idle(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " idling" << std::endl;
    // if (!state) {
    //     std::cerr << "[CHARACTER] Error: Null state for character ID: " << static_cast<int>(id)
    //     << std::endl; return;
    // }

    // auto newState = std::unique_ptr<State>(state->exec(*this, time));
    // if (newState) {
    //     std::cout << "[CHARACTER] State changed to new state" << std::endl;
    //     state = std::move(newState);
    // } else {
    //     std::cout << "[CHARACTER] State remains the same" << std::endl;
    // }

    auto newState = std::unique_ptr<State>(state->stopAction());
    if (newState) {
        state = std::move(newState);
    }
}


void Character::recvDamage(uint8_t dmg, float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " receiving damage: " << static_cast<int>(dmg) << std::endl;
    Entity::recvDamage(dmg, time);
    if (isDead) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " is dead"
                  << std::endl;
        return;
    }
    auto newState = std::unique_ptr<State>(state->receiveDamage(*this, dmg, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::update(float time) {
    std::cout << "[CHARACTER] Updating character ID: " << static_cast<int>(id) << std::endl;
    try {
        if (isIntoxicated) {
            intoxicatedTime -= time;
            if (intoxicatedTime <= 0) {
                isIntoxicated = false;
                intoxicatedTime = 0;
                std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                          << " no longer intoxicated" << std::endl;
            }
        }

        if (!state) {
            std::cerr << "[CHARACTER] Null state for character ID: " << static_cast<int>(id)
                      << std::endl;
            return;
        }
        auto newState = std::unique_ptr<State>(state->exec(*this, time));
        if (newState) {
            state = std::move(newState);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CHARACTER] Error updating character ID: " << static_cast<int>(id) << ": "
                  << e.what() << std::endl;
    }
}


void Character::shoot(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " shooting" << std::endl;
    auto newState = std::unique_ptr<State>(state->shoot(*this, std::move(currentWeapon), time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveRight(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving right"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::RIGHT, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveLeft(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving left"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::LEFT, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveUp(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving up" << std::endl;
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::UP, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::moveDown(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving down"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(*this, Direction::DOWN, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::becomeIntoxicated(float duration) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " becoming intoxicated for duration: " << duration << std::endl;
    isIntoxicated = true;
    intoxicatedTime = duration;
    auto newState = std::unique_ptr<State>(state->becomeIntoxicated(*this, duration));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::die(float respawnTime) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " dying, respawn time: " << respawnTime << std::endl;
    isDead = true;
    auto newState = std::unique_ptr<State>(state->die(*this, respawnTime));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::heal(uint8_t healQnt) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " healing, amount: " << static_cast<int>(healQnt) << std::endl;
    Entity::heal(healQnt);
}

void Character::revive(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " reviving" << std::endl;
    if (maxRevived <= 0) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                  << " cannot revive, max revives reached" << std::endl;
        return;
    }
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
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " switching weapon to type: " << static_cast<int>(type) << std::endl;
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
    auto weaponType = currentWeapon->getWeaponType();
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " current weapon type: " << static_cast<int>(weaponType) << std::endl;
    return weaponType;
}

void Character::moveRight() {
    if (isIntoxicated)
        return;

    auto mapPosition = getMapPosition(movesPerCell);
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving right"
              << " map position: " << mapPosition << std::endl;

    gameMap.moveObject(pos, mapPosition, Direction::RIGHT);
    // state = std::make_unique<MovingState>(*this, Direction::RIGHT, 0);
}

void Character::moveLeft() {
    if (isIntoxicated)
        return;

    auto mapPosition = getMapPosition(movesPerCell);
    Vector<uint8_t> newPosition = pos - Vector<uint8_t>{movesPerCell, 0};

    if (!gameMap.isValidMapPosition(newPosition))
        return;

    gameMap.moveObject(pos, mapPosition, Direction::LEFT);
}

void Character::moveUp() {
    if (isIntoxicated)
        return;

    auto mapPosition = getMapPosition(movesPerCell);
    Vector<uint8_t> newPosition = pos + Vector<uint8_t>{0, movesPerCell};

    if (!gameMap.isValidMapPosition(newPosition))
        return;

    gameMap.moveObject(pos, mapPosition, Direction::UP);
}

void Character::moveDown() {
    if (isIntoxicated)
        return;

    auto mapPosition = getMapPosition(movesPerCell);
    Vector<uint8_t> newPosition = pos - Vector<uint8_t>{0, movesPerCell};

    if (!gameMap.isValidMapPosition(newPosition))
        return;

    gameMap.moveObject(pos, mapPosition, Direction::DOWN);
}

bool Character::characIsIntoxicated() const { return isIntoxicated; }

float Character::getIntoxicatedTime() const { return intoxicatedTime; }

CharacterType Character::getCharacterType() { return type; }

PlayerDTO Character::getDTO() const {
    return PlayerDTO{pos.x,
                     pos.y,
                     id,
                     health,
                     static_cast<uint8_t>(0),
                     static_cast<uint8_t>(0),
                     type,
                     state->getCharacterState()};
}
