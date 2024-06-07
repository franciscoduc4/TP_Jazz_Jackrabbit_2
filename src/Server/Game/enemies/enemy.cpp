#include "enemy.h"

#include "../gameMap.h"

Enemy::Enemy(GameMap& gameMap, Vector<int16_t> pos, int16_t id, int16_t health, Direction dir,
             uint16_t dmg, std::unique_ptr<EnemyState> initialState, int16_t viewDistance,
             int16_t viewDistanceHit, int16_t movesPerCell, int16_t hitDistance,
             std::vector<int16_t> walkProb, std::vector<int16_t> jumpProb,
             std::vector<int16_t> flyProb):
        Entity(pos, id, health, dir),
        gameMap(gameMap),
        dmg(dmg),
        state(std::move(initialState)),
        viewDistance(viewDistance),
        viewDistanceHit(viewDistanceHit),
        movesPerCell(movesPerCell),
        hitDistance(hitDistance),
        walkProb(walkProb),
        jumpProb(jumpProb),
        flyProb(flyProb) {}

void Enemy::update(std::vector<std::shared_ptr<Character>> characters, float time) {
    std::unique_ptr<EnemyState> newState = state->update(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
    attack(characters, time);
}

void Enemy::recvDamage(uint16_t dmg, float time) {
    Entity::recvDamage(dmg, time);
    viewDistance = viewDistanceHit;
    if (isDead) {
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
    gameMap.removeEnemy(getMapPosition(movesPerCell));
    std::unique_ptr<EnemyState> newState = state->die(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
}

std::shared_ptr<Character> Enemy::getClosestCharacter(
        std::vector<std::shared_ptr<Character>> characters) {
    std::shared_ptr<Character> closestCharacter = nullptr;
    int16_t minDistance = viewDistance;
    for (auto& character: characters) {
        int16_t distance = getDistanceTo(character);
        if (distance < minDistance) {
            minDistance = distance;
            closestCharacter = character;
        }
    }
    return closestCharacter;
}

std::unique_ptr<EnemyState>& Enemy::getState() { return state; }