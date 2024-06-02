#include "gameMap.h"

GameMap::GameMap(Vector<int16_t> size): size(size), entityFactory() {}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInShootRange(Vector<int16_t> mapPosition,
                                                                     Direction dir) {
    std::vector<std::shared_ptr<Entity>> entities;
    if (dir == Direction::LEFT) {
        for (int16_t i = mapPosition.x - 1; i >= 0; i--) {
            Vector<int16_t> pos = {i, mapPosition.y};
            if (mapGrid.find(pos) != mapGrid.end()) {
                entities.push_back(mapGrid[pos]);
            }
        }
    } else if (dir == Direction::RIGHT) {
        for (int16_t i = mapPosition.x + 1; i < size.x; i++) {
            Vector<int16_t> pos = {i, mapPosition.y};
            if (mapGrid.find(pos) != mapGrid.end()) {
                entities.push_back(mapGrid[pos]);
            }
        }
    }
}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInExplosionRange(
        Vector<int16_t> mapPosition, int16_t radius) {
    std::vector<std::shared_ptr<Entity>> entities;
    for (int16_t i = mapPosition.x - radius; i <= mapPosition.x + radius; i++) {
        for (int16_t j = mapPosition.y - radius; j <= mapPosition.y + radius; j++) {
            Vector<int16_t> pos = {i, j};
            if (mapGrid.find(pos) != mapGrid.end()) {
                entities.push_back(mapGrid[pos]);
            }
        }
    }
    return entities;
}

void GameMap::moveObject(Vector<int16_t>& position, Vector<int16_t> mapPosition, Direction dir) {
    Vector<int16_t> delta;
    if (dir == Direction::LEFT) {
        if (position.x % movesPerCell != 0) {
            position.x -= 1;
            return;
        }
        delta = {-1, 0};
    } else if (dir == Direction::RIGHT) {
        if (position.x % movesPerCell != 0) {
            position.x += 1;
            return;
        }
        delta = {1, 0};
    } else if (dir == Direction::UP) {
        if (position.y % movesPerCell != 0) {
            position.y -= 1;
            return;
        }
        delta = {0, -1};
    } else if (dir == Direction::DOWN) {
        if (position.y % movesPerCell != 0) {
            position.y += 1;
            return;
        }
        delta = {0, 1};
    }

    Vector<int16_t> newPos = mapPosition + delta;
    if (isFreePosition(newPos)) {
        mapGrid[newPos] = mapGrid[mapPosition];
        mapGrid.erase(mapPosition);
        position += delta;
    } else {
        mapGrid[mapPosition]->interact(mapGrid[newPos]);
    }
}

bool GameMap::isFreePosition(Vector<int16_t> position) {
    if (!isValidPosition(position)) {
        return false;
    }
    return mapGrid.find(position) == mapGrid.end();
}

std::shared_ptr<Character> GameMap::addCharacter(CharacterType type) {
    Vector<int16_t> initPosition = getAvailablePosition();
    std::shared_ptr<Character> character;
    switch (type) {
        case CharacterType::JAZZ:
            character = entityFactory.createJazz(initPosition);
            break;
        case CharacterType::SPAZ:
            character = entityFactory.createSpaz(initPosition);
            break;
        case CharacterType::LORI:
            character = entityFactory.createLori(initPosition);
            break;
    }
    mapGrid[initPosition] = character;
    characters.push_back(character);
    return character;
}

void GameMap::addEnemy(EnemyType type) {
    Vector<int16_t> initPosition = getAvailablePosition();
    std::shared_ptr<Enemy> enemy;
    switch (type) {
        case EnemyType::WALKING_ENEMY:
            enemy = entityFactory.createWalker(initPosition);
            break;
        case EnemyType::FLYING_ENEMY:
            enemy = entityFactory.createFlyer(initPosition);
            break;
        case EnemyType::JUMPING_ENEMY:
            enemy = entityFactory.createJumper(initPosition);
            break;
    }
    mapGrid[initPosition] = enemy;
    enemies.push_back(enemy);
}

bool GameMap::isValidPosition(Vector<int16_t> position) {
    return position.x > 0 || position.x <= size.x || position.y > 0 || position.y <= size.y;
}

Vector<int16_t> GameMap::getAvailablePosition() {
    Vector<int16_t> pos;
    do {
        pos = {rand() % size.x, rand() % size.y};
    } while (mapGrid.find(pos) != mapGrid.end() && isValidPosition(pos));
    return pos;
}

void GameMap::update(float time) {
    for (auto& character: characters) {
        character->update(time);
    }
    for (auto& enemy: enemies) {
        enemy->update(time);
    }
}