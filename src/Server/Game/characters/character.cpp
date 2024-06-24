#include "character.h"
#include <algorithm>
#include "../enemies/enemy.h"
#include "../gameMap.h"
// #define CONFIG ServerConfig::getInstance()

Character::Character(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, CharacterType type,
                     float horizontalSpeed, float sprintSpeed, float verticalSpeed,
                     float jumpHeight, float shootCooldownTime, uint32_t width, uint32_t height):
        Entity(pos, playerId, ServerConfig::getCharacterInitialHealth(), Direction::RIGHT,
               EntityType::CHARACTER),
        type(type),
        gameMap(gameMap),
        maxHealth(ServerConfig::getCharacterInitialHealth()),
        reviveTime(ServerConfig::getCharacterReviveTime()),
        maxRevived(ServerConfig::getCharacterMaxRevived()),
        movesPerCell(ServerConfig::getCharacterMaxMovesPerCell()),
        timesRevived(0),
        respawnTime(ServerConfig::getCharacterRespawnTime()),
        damageTime(ServerConfig::getCharacterDamageTime()),
        intoxicatedTime(ServerConfig::getCharacterIntoxicatedTime()),
        horizontalSpeed(horizontalSpeed),
        sprintSpeed(sprintSpeed),
        verticalSpeed(verticalSpeed),
        jumpHeight(jumpHeight),
        shootCooldownTime(shootCooldownTime),
        currentWeapon(std::make_unique<Blaster>()),
        state(std::make_unique<IdleState>(*this)),
        width(width),
        height(height) {
    std::cout << "[CHARACTER] Character created with ID: " << static_cast<int>(playerId)
              << std::endl;
    currentWeapon = std::make_unique<Blaster>();
}

void Character::update(double time) {}

void Character::idle(float time) {

    auto newState = std::unique_ptr<State>(state->stopAction());
    if (newState) {
        std::cout << "[CHARACTER] idle Character ID: " << static_cast<int>(id) << " idling"
                  << std::endl;
        state = std::move(newState);
    }
}

void Character::recvDamage(uint8_t dmg, float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " receiving damage: " << static_cast<int>(dmg) << std::endl;
    
    if (isAlive()) {
        Entity::recvDamage(dmg, time);
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                  << " health after receiving damage: " << static_cast<int>(health) << std::endl;
        damageTime = time;

        if (!isAlive()) {
            state = std::make_unique<DeadState>(*this, time);
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " is now dead." << std::endl;
        } else {
            auto newState = std::unique_ptr<State>(state->receiveDamage(dmg, time));
            if (newState) {
                state = std::move(newState);
            }
        }
    } else {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " is dead"
                  << std::endl;
        return;
    }
}

void Character::update(float time) {
    if (!isAlive()) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " is dead and will not be updated." << std::endl;
        return;
    }

    std::cout << "[CHARACTER] Updating character ID: " << static_cast<int>(id) << std::endl;
    if (!state) {
        std::cerr << "[CHARACTER] Null state for character ID: " << static_cast<int>(id) << std::endl;
        return;
    }

    auto newState = std::unique_ptr<State>(state->exec(time));
    if (newState) {
        state = std::move(newState);
    }
    std::cout << "[CHARACTER] Character new state after update: " << static_cast<int>(state->getCharacterState()) << std::endl;

    std::cout << "[CHARACTER POS] Character Pos Update: " << static_cast<int>(pos.x) << ", " << static_cast<int>(pos.y) << std::endl;
}

void Character::shoot(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " shooting" << std::endl;
    if (!currentWeapon) {
        currentWeapon = std::make_unique<Blaster>();
    }

    auto newState = std::unique_ptr<State>(state->shoot(std::move(currentWeapon), time));
    std::cout << "[CHARACTER SHOOT] Character state before shooting: "
              << static_cast<int>(state->getCharacterState()) << std::endl;

    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " calling handleShooting on GameMap" << std::endl;

    gameMap.handleShooting(pos.x, 10, time, dir, id);

    if (newState) {
        state = std::move(newState);
        std::cout << "[CHARACTER] Character state after shooting: "
                  << static_cast<int>(state->getCharacterState()) << std::endl;
    } else {
        std::cerr << "[CHARACTER SHOOT] No new state returned from shoot()" << std::endl;
    }
}



void Character::handleCollision(std::shared_ptr<Enemy> enemy) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " collided with Enemy ID: " << static_cast<int>(enemy->getId()) << std::endl;

    auto enemyPos = enemy->getPosition();
    auto enemyWidth = enemy->getWidth();
    auto enemyHeight = enemy->getHeight();

    if (pos.y + height > enemyPos.y && pos.y < enemyPos.y + enemyHeight) {
        if (pos.x + width > enemyPos.x && pos.x < enemyPos.x + enemyWidth) {
            if (pos.y + height - movesPerCell <= enemyPos.y) {
                pos.y = enemyPos.y - height;  // Colisión por abajo
            } else if (pos.y >= enemyPos.y + enemyHeight - movesPerCell) {
                pos.y = enemyPos.y + enemyHeight;  // Colisión por arriba
            } else if (pos.x + width - movesPerCell <= enemyPos.x) {
                pos.x = enemyPos.x - width;  // Colisión por la izquierda
            } else if (pos.x >= enemyPos.x + enemyWidth - movesPerCell) {
                pos.x = enemyPos.x + enemyWidth;  // Colisión por la derecha
            }
        }
    }

    auto newState = std::make_unique<IdleState>(*this);
    if (newState) {
        state = std::move(newState);
    }
}

void Character::handleObstacleCollision(std::shared_ptr<Obstacle> obstacle) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " collided with Obstacle at position: (" << obstacle->getPosition().x << ", "
              << obstacle->getPosition().y << ")" << std::endl;

    auto obstaclePos = obstacle->getPosition();
    auto obstacleWidth = obstacle->getWidth();
    auto obstacleHeight = obstacle->getHeight();
    auto characterWidth = getWidth();
    auto characterHeight = getHeight();

    ObstacleType obstacleType = obstacle->getObstacleType();

    if (obstacleType == ObstacleType::LEFT_LADDER || obstacleType == ObstacleType::RIGHT_LADDER) {
        // Verificar colisión con el triángulo de la escalera
        Vector<uint32_t> p1, p2, p3;
        if (obstacleType == ObstacleType::LEFT_LADDER) {
            p1 = obstaclePos;
            p2 = {obstaclePos.x + obstacleWidth, obstaclePos.y};
            p3 = {obstaclePos.x, obstaclePos.y + obstacleHeight};
        } else if (obstacleType == ObstacleType::RIGHT_LADDER) {
            p1 = {obstaclePos.x, obstaclePos.y};
            p2 = {obstaclePos.x + obstacleWidth, obstaclePos.y};
            p3 = {obstaclePos.x + obstacleWidth, obstaclePos.y + obstacleHeight};
        }

        // Verificar si alguno de los cuatro puntos del personaje está dentro del triángulo
        Vector<uint32_t> characterPoints[] = {
            {pos.x, pos.y},
            {pos.x + characterWidth, pos.y},
            {pos.x, pos.y + characterHeight},
            {pos.x + characterWidth, pos.y + characterHeight}
        };

        bool collisionDetected = false;
        for (const auto& point : characterPoints) {
            if (isPointInTriangle(point, p1, p2, p3)) {
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected) {
            // Resolver la colisión
            // Ajustar la posición del personaje para "alinearlo" con la escalera
            if (obstacleType == ObstacleType::LEFT_LADDER) {
                float slope = static_cast<float>(obstacleHeight) / obstacleWidth;
                pos.y = obstaclePos.y + static_cast<uint32_t>(slope * (pos.x - obstaclePos.x)) - characterHeight;
            } else {
                float slope = static_cast<float>(obstacleHeight) / obstacleWidth;
                pos.y = obstaclePos.y + static_cast<uint32_t>(slope * (obstaclePos.x + obstacleWidth - pos.x)) - characterHeight;
            }
            onGround = true;
        }
    } else {
        // Manejo de colisión regular (rectángulo)
        if (pos.y + characterHeight >= obstaclePos.y) {
            if (pos.x + characterWidth < obstaclePos.x || pos.x > obstaclePos.x + obstacleWidth) {
                return;
            }
            onGround = true;
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                      << " collided with obstacle from below" << std::endl;
            pos.y = obstaclePos.y - characterHeight;  // Colisión por abajo
        } else if (pos.y <= obstaclePos.y + obstacleHeight) {
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                      << " collided with obstacle from above" << std::endl;
            pos.y = obstaclePos.y + obstacleHeight;  // Colisión por arriba
        } else if (pos.x + characterWidth >= obstaclePos.x) {
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                      << " collided with obstacle from the left" << std::endl;
            pos.x = obstaclePos.x - characterWidth;  // Colisión por la izquierda
        } else if (pos.x <= obstaclePos.x + obstacleWidth) {
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
                      << " collided with obstacle from the right" << std::endl;
            pos.x = obstaclePos.x + obstacleWidth;  // Colisión por la derecha
        }
    }
}

void Character::handleCharacterCollision(std::shared_ptr<Character> character) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " collided with Character ID: " << static_cast<int>(character->getId())
              << std::endl;

    auto characterPos = character->getPosition();
    auto characterWidth = character->getWidth();
    auto characterHeight = character->getHeight();

    if (pos.y + height > characterPos.y && pos.y < characterPos.y + characterHeight) {
        if (pos.x + width > characterPos.x && pos.x < characterPos.x + characterWidth) {
            if (pos.y + height - movesPerCell <= characterPos.y) {
                pos.y = characterPos.y - height;  // Colisión por abajo
            } else if (pos.y >= characterPos.y + characterHeight - movesPerCell) {
                pos.y = characterPos.y + characterHeight;  // Colisión por arriba
            } else if (pos.x + width - movesPerCell <= characterPos.x) {
                pos.x = characterPos.x - width;  // Colisión por la izquierda
            } else if (pos.x >= characterPos.x + characterWidth - movesPerCell) {
                pos.x = characterPos.x + characterWidth;  // Colisión por la derecha
            }
        }
    }

    auto newState = std::make_unique<IdleState>(*this);
    if (newState) {
        state = std::move(newState);
    }
}


void Character::handleLadderCollision(std::shared_ptr<Obstacle> obstacle) {
    auto obstaclePos = obstacle->getPosition();
    auto obstacleWidth = obstacle->getWidth();
    auto obstacleHeight = obstacle->getHeight();

    if (obstacle->getObstacleType() == ObstacleType::LEFT_LADDER) {
        float slope = static_cast<float>(obstacleHeight) / obstacleWidth;
        pos.y = obstaclePos.y + static_cast<uint32_t>(slope * (pos.x - obstaclePos.x));
    } else if (obstacle->getObstacleType() == ObstacleType::RIGHT_LADDER) {
        float slope = static_cast<float>(obstacleHeight) / obstacleWidth;
        pos.y = obstaclePos.y + static_cast<uint32_t>(slope * (obstaclePos.x + obstacleWidth - pos.x));
    }
    
    onGround = true;
}


bool Character::isPointInTriangle(const Vector<uint32_t>& p, const Vector<uint32_t>& v1, 
    const Vector<uint32_t>& v2, const Vector<uint32_t>& v3) {
    auto sign = [](const Vector<uint32_t>& p1, const Vector<uint32_t>& p2, const Vector<uint32_t>& p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    };

    bool b1, b2, b3;

    b1 = sign(p, v1, v2) < 0.0f;
    b2 = sign(p, v2, v3) < 0.0f;
    b3 = sign(p, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}




void Character::moveRight(double time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving right"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(Direction::RIGHT, time));
    dir = Direction::RIGHT;  

    if (newState) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving right"
                  << std::endl;
        state = std::move(newState);
    }
}

void Character::moveLeft(double time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving left"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(Direction::LEFT, time));
    dir = Direction::LEFT; 

    if (newState) {
        state = std::move(newState);
    }
}

void Character::jump(float time) {
    if (onGround) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " jumping" << std::endl;
        auto newState = std::unique_ptr<State>(state->move(Direction::UP, time));
        if (newState) {
            std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " jumping" << std::endl;
            state = std::move(newState);
        }
    }
}

void Character::moveDown() {
    std::cout << "[MOVE DOWN] Character ID: " << static_cast<int>(id) << " moving down"
              << std::endl;
    Vector<uint32_t> newPos = pos + Vector<uint32_t>{0, static_cast<uint32_t>(movesPerCell * 4)};
    if (newPos.y >= gameMap.getMaxYPos()) {
        newPos = Vector<uint32_t>{pos.x, gameMap.getMaxYPos()};
    }

    if (!gameMap.isValidMapPosition(newPos))
        return;

    auto entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos) {
        if (entityAtNewPos->getType() == EntityType::ENEMY) {
            gameMap.handleCharacterEnemyCollision(shared_from_this(),
                                                  std::dynamic_pointer_cast<Enemy>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::OBSTACLE) {
            gameMap.handleCharacterObstacleCollision(
                shared_from_this(), std::dynamic_pointer_cast<Obstacle>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::CHARACTER) {
            handleCharacterCollision(std::dynamic_pointer_cast<Character>(entityAtNewPos));
            return;
        }
    }
    
    pos = newPos;
    std::cout << "[CHARACTER] NEW POS Character ID: " << static_cast<int>(id)
              << " new y: " << int(pos.y) << std::endl;

    // // Check for item collision after moving
    entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos && entityAtNewPos->getType() == EntityType::ITEM) {
        gameMap.handleCharacterItemCollision(shared_from_this(),
        std::dynamic_pointer_cast<Item>(entityAtNewPos));
    }
}

void Character::moveDown(float time) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " moving down"
              << std::endl;
    auto newState = std::unique_ptr<State>(state->move(Direction::DOWN, time));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::becomeIntoxicated(float duration) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " becoming intoxicated for duration: " << duration << std::endl;
    isIntoxicated = true;
    intoxicatedTime = duration;
    auto newState = std::unique_ptr<State>(state->becomeIntoxicated(duration));
    if (newState) {
        state = std::move(newState);
    }
}

void Character::die(float respawnTime) {
    std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id)
              << " dying, respawn time: " << respawnTime << std::endl;
    isDead = true;
    auto newState = std::unique_ptr<State>(state->die(respawnTime));
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
    auto newState = std::unique_ptr<State>(state->revive(time));
    if (newState) {
        state = std::move(newState);
    }
    health = initialHealth;
    isDead = false;
}

std::vector<std::shared_ptr<Entity>> Character::getTargets() {
    std::vector<std::shared_ptr<Entity>> targets;
    gameMap.getObjectsInShootRange({static_cast<unsigned char>(pos.x / movesPerCell),
                                    static_cast<unsigned char>(pos.y / movesPerCell)},
                                   dir);
    std::cout << "[CHARACTER] targets size: " << targets.size() << std::endl;
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

    uint8_t movesPerCellX = onGround ? static_cast<uint32_t>(this->movesPerCell * 4)
     : static_cast<uint32_t>(this->movesPerCell * 2);
    auto mapPositionX = getMapPosition(movesPerCellX);

    uint8_t movesPerCellY = onGround ? 0 : static_cast<uint32_t>(this->movesPerCell);
    auto mapPositionY = getMapPosition(movesPerCellY);

    Vector<uint32_t> newPos = pos + Vector<uint32_t>{movesPerCellX, movesPerCellY};

    // Vector<uint32_t> newPos = pos + Vector<uint32_t>{1, 0};

    if (newPos.x >= gameMap.getMaxXPos()) {
        newPos = Vector<uint32_t>{gameMap.getMaxXPos(), pos.y};
    }

    if (!gameMap.isValidMapPosition(newPos))
        return;

    auto entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos) {
        if (entityAtNewPos->getType() == EntityType::ENEMY) {
            gameMap.handleCharacterEnemyCollision(shared_from_this(),
                                                  std::dynamic_pointer_cast<Enemy>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::OBSTACLE) {
            gameMap.handleCharacterObstacleCollision(
                shared_from_this(), std::dynamic_pointer_cast<Obstacle>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::CHARACTER) {
            handleCharacterCollision(std::dynamic_pointer_cast<Character>(entityAtNewPos));
            return;
        }
    }

    pos = newPos;
    std::cout << "[CHARACTER] NEW POS Character ID: " << static_cast<int>(id)
              << " new x : " << int(pos.x) << std::endl;

    // Check for item collision after moving
    entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos && entityAtNewPos->getType() == EntityType::ITEM) {
        gameMap.handleCharacterItemCollision(shared_from_this(),
                                             std::dynamic_pointer_cast<Item>(entityAtNewPos));
    }
}

void Character::moveLeft() {
    if (isIntoxicated)
        return;

    uint8_t movesPerCellX = onGround ? static_cast<uint32_t>(this->movesPerCell * 4)
     : static_cast<uint32_t>(this->movesPerCell * 2);
    auto mapPositionX = getMapPosition(movesPerCellX);

    uint8_t movesPerCellY = onGround ? 0 : static_cast<uint32_t>(this->movesPerCell);
    auto mapPositionY = getMapPosition(movesPerCellY);


    Vector<uint32_t> newPos = pos - Vector<uint32_t>{movesPerCellX, movesPerCellY};

    // Vector<uint32_t> newPos = pos - Vector<uint32_t>{1, 0};

    if (newPos.x <= 0) {
        newPos = Vector<uint32_t>{0, pos.y};
    }

    if (!gameMap.isValidMapPosition(newPos))
        return;

    auto entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos) {
        if (entityAtNewPos->getType() == EntityType::ENEMY) {
            gameMap.handleCharacterEnemyCollision(shared_from_this(),
                                                  std::dynamic_pointer_cast<Enemy>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::OBSTACLE) {
            gameMap.handleCharacterObstacleCollision(
                shared_from_this(), std::dynamic_pointer_cast<Obstacle>(entityAtNewPos));
            return;
        } else if (entityAtNewPos->getType() == EntityType::CHARACTER) {
            handleCharacterCollision(std::dynamic_pointer_cast<Character>(entityAtNewPos));
            return;
        }
    }

    pos = newPos;
    std::cout << "[CHARACTER] NEW POS Character ID: " << static_cast<int>(id)
              << " new x : " << int(pos.x) << std::endl;

    // Check for item collision after moving
    entityAtNewPos = gameMap.getEntityAt(newPos);
    if (entityAtNewPos && entityAtNewPos->getType() == EntityType::ITEM) {
        gameMap.handleCharacterItemCollision(shared_from_this(),
                                             std::dynamic_pointer_cast<Item>(entityAtNewPos));
    }
}

void Character::jump() {
    if (onGround) {
        std::cout << "[CHARACTER] Character ID: " << static_cast<int>(id) << " initiating jump" << std::endl;
        initialYJump = pos.y;
        jumping = true;
        onGround = false;
        for (int i = 0; i < 20; i++) {
            uint32_t newPosY = pos.y - i;
            if (gameMap.isValidMapPosition({pos.x, newPosY})) {
                pos.y = newPosY;
            }
        }
        jumping = false;
    }
}


bool Character::hasLanded() {
    if (pos.y == initialYJump && !jumping)
        return true;
    return false;
}

bool Character::isOnGround() const {
    return onGround;
}


bool Character::characIsIntoxicated() const { return isIntoxicated; }

float Character::getIntoxicatedTime() const { return intoxicatedTime; }

CharacterType Character::getCharacterType() { return type; }

void Character::collectItem(const std::shared_ptr<Item>& item) {
    switch (item->getItemType()) {
        case ItemType::FOOD:
            heal(item->getValue());
            std::cout << "[CHARACTER] Collected food. Health increased to: " <<
            static_cast<int>(health) << std::endl;
            break;
        case ItemType::GEM:
            score += item->getValue();
            std::cout << "[CHARACTER] Collected gem. Score increased to: " <<
            static_cast<int>(score) << std::endl;
            break;
        case ItemType::SILVER_COIN:
            score += item->getValue();
            std::cout << "[CHARACTER] Collected silver coin. Score increased to: " <<
            static_cast<int>(score) << std::endl;
            break;
        case ItemType::GOLD_COIN:
            score += item->getValue();
            std::cout << "[CHARACTER] Collected gold coin" << std::endl;
            break;
        default:
            std::cerr << "[CHARACTER] Unknown item type collected." << std::endl;
            break;
    }
}

void Character::setState(std::unique_ptr<State> newState) {
    state = std::move(newState);
}

PlayerDTO Character::getDTO() const {
    return PlayerDTO{pos.x,
                     pos.y,
                     id,
                     health,
                     static_cast<uint8_t>(0),
                     static_cast<uint8_t>(0),
                     type,
                     state->getCharacterState(),
                     score};
}

uint32_t Character::getWidth() const { return width; }

uint32_t Character::getHeight() const { return height; }

void Character::setOnGround(bool onGround) { this->onGround = onGround; }