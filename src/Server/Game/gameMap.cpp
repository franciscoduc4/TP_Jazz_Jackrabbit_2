#include "gameMap.h"

GameMap::GameMap(Vector<int16_t> size): size(size), entityFactory(*this) {}

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
    return entities;
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
        auto character = std::dynamic_pointer_cast<Character>(mapGrid[mapPosition]);
        character->interact(mapGrid[newPos]);
    }
}

bool GameMap::isFreePosition(Vector<int16_t> position) {
    if (!isValidPosition(position)) {
        return false;
    }
    return mapGrid.find(position) == mapGrid.end();
}


void GameMap::addEntityToMap(std::shared_ptr<Entity> entity, Vector<int16_t> position) {
    if (isFreePosition(position)) {
        mapGrid[position] = entity;
    } else {
        position = getAvailablePosition();
        mapGrid[position] = entity;
    }
}

std::shared_ptr<Character> GameMap::addCharacter(int32_t playerId, CharacterType type,
                                                 std::optional<Vector<int16_t>> position) {
    Vector<int16_t> initPosition = position ? *position : getAvailablePosition();
    auto character = entityFactory.createCharacter(entityCount, type, initPosition);
    characters[playerId] = character;
    addEntityToMap(character, initPosition);
    entityCount++;
    return character;
}

void GameMap::addEnemy(EnemyType type, std::optional<Vector<int16_t>> position) {
    Vector<int16_t> initPosition = position ? *position : getAvailablePosition();
    auto enemy = entityFactory.createEnemy(entityCount, type, initPosition);
    entityCount++;
    addEntityToMap(enemy, initPosition);
}

bool GameMap::isValidPosition(Vector<int16_t> position) {
    return position.x > 0 || position.x <= size.x || position.y > 0 || position.y <= size.y;
}

Vector<int16_t> GameMap::getAvailablePosition() {
    Vector<int16_t> pos;
    do {
        pos = {static_cast<int16_t>(rand() % size.x), static_cast<int16_t>(rand() % size.y)};
    } while (mapGrid.find(pos) != mapGrid.end() && isValidPosition(pos));
    return pos;
}

void GameMap::update(float time) {
    for (auto& [_, entity]: mapGrid) {
        auto character = std::dynamic_pointer_cast<Character>(entity);
        character->update(time);
    }
}

void GameMap::removeCharacter(int32_t playerId) {
    auto character = characters[playerId];
    mapGrid.erase(character->getPosition());
}

void GameMap::removeEnemy(Vector<int16_t> position) { mapGrid.erase(position); }

std::shared_ptr<Entity> GameMap::getEntityAt(Vector<int16_t> position) {
    if (isValidPosition(position) && mapGrid.find(position) != mapGrid.end()) {
        return mapGrid[position];
    }
    return nullptr;
}

std::unique_ptr<GameDTO> GameMap::getGameDTO() {
    GameDTO gameDTO;
    return std::make_unique<GameDTO>(gameDTO);
}

std::shared_ptr<Character> GameMap::getCharacter(int32_t playerId) { return characters[playerId]; }