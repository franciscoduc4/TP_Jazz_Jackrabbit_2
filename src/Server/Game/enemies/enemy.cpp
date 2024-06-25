#include "enemy.h"

#include "../gameMap.h"

Enemy::Enemy(GameMap& gameMap, const Vector<uint32_t>& pos, uint8_t id, uint8_t health,
             Direction dir, uint8_t dmg, std::unique_ptr<EnemyState> initialState,
             uint8_t viewDistance, uint8_t viewDistanceHit, uint8_t movesPerCell,
             uint8_t hitDistance, std::vector<uint8_t> walkProb, std::vector<uint8_t> jumpProb,
             std::vector<uint8_t> flyProb, uint32_t width, uint32_t height):
        Entity(pos, id, health, dir, EntityType::ENEMY),
        gameMap(gameMap),
        dmg(dmg),
        state(std::move(initialState)),
        viewDistance(viewDistance),
        viewDistanceHit(viewDistanceHit),
        movesPerCell(movesPerCell),
        hitDistance(hitDistance),
        walkProb(walkProb),
        jumpProb(jumpProb),
        flyProb(flyProb),
        width(width),
        height(height),
        initialPosition(pos),
        movingRight(true) {}

void Enemy::update(const std::map<uint8_t, std::shared_ptr<Character>>& characters, float time) {

    // std::cout << "[ENEMY] update" << std::endl;

    std::vector<std::shared_ptr<Character>> characterList;
    for (const auto& pair: characters) {
        characterList.push_back(pair.second);
    }

    std::unique_ptr<EnemyState> newState = state->update(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
}


void Enemy::recvDamage(uint8_t dmg, float time) {
    std::cout << "[ENEMY] recvDamage" << std::endl;
    Entity::recvDamage(dmg);
    if (isDead()) {
        die(time);
        return;
    } else {
        std::unique_ptr<EnemyState> newState = state->receivingDmg(time);
        if (newState != nullptr) {
            state = std::move(newState);
        }
    }
}

void Enemy::attack(std::vector<std::shared_ptr<Character>> characters, float time) {
    std::shared_ptr<Character> closeCharacter = getClosestCharacter(characters);
    if (!closeCharacter) {
        return;
    }
    if (getDistanceTo(closeCharacter) <= hitDistance) {
        std::unique_ptr<EnemyState> newState = state->attackCharacter(closeCharacter, dmg, time);
        if (newState != nullptr) {
            state = std::move(newState);
        }
    } else {
        return;
    }
}

void Enemy::die(float time) {
    Entity::die(time);
    std::unique_ptr<EnemyState> newState = state->die(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
}

std::shared_ptr<Character> Enemy::getClosestCharacter(
        std::vector<std::shared_ptr<Character>> characters) {
    std::shared_ptr<Character> closestCharacter = nullptr;
    uint8_t minDistance = viewDistance;
    for (auto& character: characters) {
        uint8_t distance = getDistanceTo(character);
        if (distance < minDistance) {
            minDistance = distance;
            closestCharacter = character;
        }
    }
    return closestCharacter;
}

std::unique_ptr<EnemyState>& Enemy::getState() { return state; }


EnemyDTO Enemy::getDTO() const {
    return EnemyDTO{
            pos.x, pos.y, id, health, dmg, static_cast<uint32_t>(0), getEnemyType(), EnemyStateEntity::ENEMY_WALKING};
}

void Enemy::update(double deltaTime) { }
