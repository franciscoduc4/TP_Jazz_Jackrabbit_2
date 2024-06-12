#include "gameMap.h"

#include <iostream>

#define CONFIG ServerConfig::getInstance()

// Vector<int16_t> size;
// std::map<Vector<int16_t>, std::shared_ptr<Entity>> mapGrid;
// std::map<int16_t, std::shared_ptr<Character>> characters;
// EntityFactory entityFactory;
// int16_t movesPerCell;
// float gravity;
// std::string episodeName;

GameMap::GameMap(Vector<int16_t> size, std::string episodeName):
        size(size),
        entityFactory(*this),
        gravity(CONFIG->getGameGravity()),
        episodeName(episodeName) {}

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
    Vector<int16_t> newPosition = calculateNewPosition(position, dir);
    Vector<int16_t> newMapPosition = getMapPosition(newPosition, movesPerCell);

    if (!isValidPosition(newPosition))
        return;

    if (!handleMovement(position, mapPosition, newPosition, newMapPosition)) {
        auto character = std::dynamic_pointer_cast<Character>(mapGrid[mapPosition]);
        if (character && !isFreePosition(newMapPosition)) {
            character->interact(mapGrid[newMapPosition]);
        }
    }
}

bool GameMap::isFreePosition(Vector<int16_t> position) {
    return mapGrid.find(position) == mapGrid.end();
}


void GameMap::addEntityToMap(std::shared_ptr<Entity> entity, Vector<int16_t> position) {
    Vector<int16_t> mapPosition = entity->getMapPosition(movesPerCell);
    if (isFreePosition(mapPosition)) {
        mapGrid[mapPosition] = entity;
    } else {
        position = getAvailablePosition();
        mapGrid[position] = entity;
    }
}

std::shared_ptr<Character> GameMap::addCharacter(
        uint32_t playerId, CharacterType type,
        std::optional<Vector<int16_t>> position = std::nullopt) {
    Vector<int16_t> initPosition = position ? *position : getAvailablePosition();
    if (!isValidMapPosition(initPosition)) {
        return nullptr;
    }

    auto character = entityFactory.createCharacter(entityCount, type, initPosition);
    if (!character) {
        return nullptr;
    }

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

bool GameMap::isValidMapPosition(Vector<int16_t> mapPosition) {
    return mapPosition.x >= 0 && mapPosition.x <= size.x && mapPosition.y >= 0 &&
           mapPosition.y <= size.y;
}

bool GameMap::isValidPosition(Vector<int16_t> position) {
    return position.x >= 0 && position.x <= size.x * movesPerCell && position.y >= 0 &&
           position.y <= size.y * movesPerCell;
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

void GameMap::removeCharacter(uint32_t playerId) {
    auto character = characters[playerId];
    mapGrid.erase(character->getPosition());
}

void GameMap::removeEnemy(Vector<int16_t> position) { mapGrid.erase(position); }

std::shared_ptr<Entity> GameMap::getEntityAt(Vector<int16_t> mapPosition) {
    if (isValidPosition(mapPosition) && mapGrid.find(mapPosition) != mapGrid.end()) {
        return mapGrid[mapPosition];
    }
    return nullptr;
}

std::unique_ptr<GameDTO> GameMap::getGameDTO() {
    GameDTO gameDTO;
    return std::make_unique<GameDTO>(gameDTO);
    // COMPLETAR
}

std::shared_ptr<Character> GameMap::getCharacter(uint32_t playerId) { return characters[playerId]; }

void GameMap::printMapGrid() const {
    for (const auto& pair: mapGrid) {
        std::cout << "Key: (" << pair.first.x << ", " << pair.first.y << "), "
                  << "Value: " << pair.second->getMapPosition(movesPerCell)
                  << " - ID: " << pair.second->getId() << std::endl;
    }
}

Vector<int16_t> GameMap::getMapPosition(Vector<int16_t> position, int16_t movesPerCell) {
    return {static_cast<int16_t>(position.x / movesPerCell),
            static_cast<int16_t>(position.y / movesPerCell)};
}

Vector<int16_t> GameMap::calculateNewPosition(const Vector<int16_t>& position,
                                              Direction dir) const {
    switch (dir) {
        case Direction::LEFT:
            return position - Vector<int16_t>{1, 0};
        case Direction::RIGHT:
            return position + Vector<int16_t>{1, 0};
        case Direction::UP:
            return position + Vector<int16_t>{0, 1};
        case Direction::DOWN:
            return position - Vector<int16_t>{0, 1};
        default:
            return position;
    }
}

bool GameMap::handleMovement(Vector<int16_t>& position, Vector<int16_t> mapPosition,
                             const Vector<int16_t>& newPosition,
                             const Vector<int16_t>& newMapPosition) {
    if (newMapPosition == mapPosition) {
        if (isValidPosition(newPosition)) {
            position = newPosition;
            return true;
        }
    } else if (isValidMapPosition(newMapPosition) && isFreePosition(newMapPosition)) {
        mapGrid[newMapPosition] = mapGrid[mapPosition];
        mapGrid.erase(mapPosition);
        position = newPosition;
        return true;
    }
    return false;
}