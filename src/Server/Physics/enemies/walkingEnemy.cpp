#include "walkingEnemy.h"

#include <utility>

#include "../gameMap.h"

WalkingEnemy::WalkingEnemy(int16_t x, int16_t y, int16_t id, GameMap& map, int16_t health,
                           int16_t dmg):
        movesPerCell(2),
        x(x),
        y(y),
        id(id),
        map(map),
        health(health),
        dmg(dmg),
        hitDistance(1),
        hitDistanceY(1),
        viewDistance(5),
        viewDistanceHit(1),
        walkProb({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
        flyProb({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
        jumpProb({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) {}  // todo esto saldria del YAML


void WalkingEnemy::update(std::vector<std::shared_ptr<Character>> characters, float time) {
    std::unique_ptr<EnemyState> newState = state->update(time);
    if (newState != nullptr) {
        state.reset();
        state = std::move(newState);
    }
    attack(characters, time);
}

void WalkingEnemy::receiveDmg(int16_t dmg, float time) {
    health -= dmg;
    viewDistance = viewDistanceHit;
    if (health <= 0) {
        die(time);
        return;
    } else {
        std::unique_ptr<EnemyState> newState = state->receivingDmg(time);
        if (newState != nullptr) {
            state.reset();
            state = std::move(newState);
        }
    }
}

void WalkingEnemy::attack(std::vector<std::shared_ptr<Character>> characters, float time) {
    std::shared_ptr<Character> closeCharacter = getClosestCharacter(characters);
    if (!closeCharacter) {
        return;
    }
    if (getDistanceToCharacter(closeCharacter) <= hitDistance ||
        getDistanceToCharacter(closeCharacter) <= hitDistanceY) {
        std::unique_ptr<EnemyState> newState = state->attackCharacter(closeCharacter, dmg, time);
        if (newState != nullptr) {
            state.reset();
            state = std::move(newState);
        }
    } else {
        return;
    }
}

void WalkingEnemy::die(float time) {
    isDead = true;
    map.removeEnemy({getMatrixX(), getMatrixY()});
    std::unique_ptr<EnemyState> newState = state->die(time);
    if (newState != nullptr) {
        state.reset();
        state = std::move(newState);
    }
}

void WalkingEnemy::setDir(int16_t dir) { this->dir = dir; }

int16_t WalkingEnemy::getX() { return x; }

int16_t WalkingEnemy::getY() { return y; }

int16_t WalkingEnemy::getMatrixX() { return x / movesPerCell; }

int16_t WalkingEnemy::getMatrixY() { return y / movesPerCell; }

int16_t WalkingEnemy::getId() { return id; }

int16_t WalkingEnemy::getHealth() { return health; }

int16_t WalkingEnemy::getDistanceToCharacter(std::shared_ptr<Character> character) {
    return abs(getXDistanceToCharacter(character)) + abs(getYDistanceToCharacter(character));
}

int16_t WalkingEnemy::getXDistanceToCharacter(std::shared_ptr<Character> character) {
    return character->getX() - x;
}

int16_t WalkingEnemy::getYDistanceToCharacter(std::shared_ptr<Character> character) {
    return character->getY() - y;
}

std::shared_ptr<Character> WalkingEnemy::getClosestCharacter(
        std::vector<std::shared_ptr<Character>> characters) {
    std::shared_ptr<Character> closestCharacter = nullptr;
    int16_t minDistance = viewDistance;
    for (auto& character: characters) {
        int16_t distance = getDistanceToCharacter(character);
        if (distance < minDistance) {
            minDistance = distance;
            closestCharacter = character;
        }
    }
    return closestCharacter;
}
