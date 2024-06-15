#include "gameMap.h"

#include <iostream>
#include <optional>

#include "../../Common/maps/mapsManager.h"

#define CONFIG ServerConfig::getInstance()

GameMap::GameMap(Vector<uint8_t> size, uint8_t mapId):
        size(size),
        entityFactory(*this),
        gravity(CONFIG->getGameGravity()),
        movesPerCell(CONFIG->getGameMaxMoves()),
        mapId(mapId) {
    std::cout << "[GAMEMAP] GameMap created with mapId: " << static_cast<int>(mapId) << std::endl;
}

void GameMap::loadMap(uint8_t mapId) {
    try {
        std::string filePath = MapsManager::getMapFileNameById(mapId);
        std::cout << "[GAMEMAP] Loading map from file: " << filePath << std::endl;

        YAML::Node config = YAML::LoadFile(filePath);
        std::cout << "[GAMEMAP] YAML file loaded" << std::endl;

        if (!config["SIZE"] || !config["SIZE"]["WIDTH"] || !config["SIZE"]["HEIGHT"]) {
            throw std::runtime_error("Invalid map size configuration in YAML file");
        }
        size.x = config["SIZE"]["WIDTH"].as<uint8_t>();
        size.y = config["SIZE"]["HEIGHT"].as<uint8_t>();
        std::cout << "[GAMEMAP] Map size: Width = " << static_cast<int>(size.x)
                  << ", Height = " << static_cast<int>(size.y) << std::endl;

        if (size.x <= 0 || size.y <= 0) {
            throw std::runtime_error("Map size must be positive non-zero values");
        }

        if (config["ENEMIES"]) {
            for (const auto& enemy: config["ENEMIES"]) {
                auto enemyType = enemy.first.as<std::string>();
                std::cout << "[GAMEMAP] Enemy type: " << enemyType << std::endl;
                for (const auto& pos: enemy.second) {
                    if (pos.size() != 2) {
                        throw std::runtime_error(
                                "Invalid enemy position configuration in YAML file");
                    }
                    Vector<uint8_t> position = {pos[0].as<uint8_t>(), pos[1].as<uint8_t>()};
                    std::cout << "[GAMEMAP] Enemy position: (" << static_cast<int>(position.x)
                              << ", " << static_cast<int>(position.y) << ")" << std::endl;
                    EnemyType type = getEnemyType(enemyType);
                    addEnemy(type, position);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error loading map: " << e.what() << std::endl;
        throw;
    }
}

EnemyType GameMap::getEnemyType(const std::string& type) {
    try {
        if (type == "TURTLES")
            return EnemyType::TURTLE;
        if (type == "SCHWARZENGUARDS")
            return EnemyType::SCHWARZENGUARD;
        if (type == "YELLOWMONS")
            return EnemyType::YELLOWMON;
        throw std::runtime_error("Unknown enemy type");
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting enemy type: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInShootRange(Vector<uint8_t> mapPosition,
                                                                     Direction dir) {
    std::vector<std::shared_ptr<Entity>> entities;
    try {
        if (dir == Direction::LEFT) {
            for (int8_t i = mapPosition.x - 1; i >= 0; i--) {
                Vector<uint8_t> pos = {static_cast<uint8_t>(i), mapPosition.y};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        } else if (dir == Direction::RIGHT) {
            for (uint8_t i = mapPosition.x + 1; i < size.x; i++) {
                Vector<uint8_t> pos = {i, mapPosition.y};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting objects in shoot range: " << e.what() << std::endl;
    }
    return entities;
}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInExplosionRange(
        Vector<uint8_t> mapPosition, uint8_t radius) {
    std::vector<std::shared_ptr<Entity>> entities;
    try {
        for (int8_t i = mapPosition.x - radius; i <= mapPosition.x + radius; i++) {
            for (int8_t j = mapPosition.y - radius; j <= mapPosition.y + radius; j++) {
                Vector<uint8_t> pos = {static_cast<uint8_t>(i), static_cast<uint8_t>(j)};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting objects in explosion range: " << e.what()
                  << std::endl;
    }
    return entities;
}

void GameMap::moveObject(Vector<uint8_t>& position, Vector<uint8_t> mapPosition, Direction dir) {
    try {
        auto character = std::dynamic_pointer_cast<Character>(mapGrid[mapPosition]);
        if (!character) {
            std::cerr << "[GAMEMAP] Invalid character" << std::endl;
            return;
        }

        Vector<uint8_t> newPosition = calculateNewPosition(position, dir);
        Vector<uint8_t> newMapPosition = getMapPosition(newPosition);
        if (!handleMovement(position, mapPosition, newPosition, newMapPosition)) {
            character->interact(mapGrid[newMapPosition]);
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error moving object: " << e.what() << std::endl;
    }
}

bool GameMap::isFreePosition(Vector<uint8_t> position) {
    return mapGrid.find(position) == mapGrid.end();
}

void GameMap::addEntityToMap(std::shared_ptr<Entity> entity, Vector<uint8_t> position) {
    try {
        Vector<uint8_t> mapPosition = entity->getMapPosition(movesPerCell);
        std::cout << "[GAMEMAP] Adding entity at position: (" << static_cast<int>(mapPosition.x)
                  << ", " << static_cast<int>(mapPosition.y) << ")" << std::endl;
        if (isFreePosition(mapPosition)) {
            mapGrid[mapPosition] = entity;
        } else {
            position = getAvailablePosition();
            mapGrid[position] = entity;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding entity to map: " << e.what() << std::endl;
    }
}

Vector<uint8_t> GameMap::getInitialPositionForCharacterType(CharacterType type) {
    try {
        std::string filePath = MapsManager::getMapFileNameById(mapId);
        YAML::Node config = YAML::LoadFile(filePath);

        std::string characterTypeStr;
        switch (type) {
            case CharacterType::JAZZ:
                characterTypeStr = "JAZZ";
                break;
            case CharacterType::SPAZ:
                characterTypeStr = "SPAZ";
                break;
            case CharacterType::LORI:
                characterTypeStr = "LORI";
                break;
            default:
                throw std::runtime_error("Unknown character type");
        }

        for (const auto& pos: config["PLAYERS"][characterTypeStr]) {
            if (pos.size() != 2) {
                throw std::runtime_error("Invalid player position configuration in YAML file for " +
                                         characterTypeStr);
            }
            return {pos[0].as<uint8_t>(), pos[1].as<uint8_t>()};
        }

        throw std::runtime_error("Initial position for character type not found in YAML for " +
                                 characterTypeStr);
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting initial position for character type: " << e.what()
                  << std::endl;
        throw;
    }
}

std::shared_ptr<Character> GameMap::addCharacter(uint8_t playerId, CharacterType type) {
    try {
        Vector<uint8_t> initPosition = getInitialPositionForCharacterType(type);

        if (!isValidMapPosition(initPosition)) {
            std::cerr << "[GAMEMAP] Invalid initial position for character" << std::endl;
            return nullptr;
        }

        auto character = entityFactory.createCharacter(playerId, type, initPosition);
        if (!character) {
            std::cerr << "[GAMEMAP] Failed to create character" << std::endl;
            return nullptr;
        }

        characters[playerId] = character;
        addEntityToMap(character, initPosition);
        entityCount++;
        std::cout << "[GAMEMAP] Character with ID " << static_cast<int>(playerId) << " added"
                  << std::endl;
        return character;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding character: " << e.what() << std::endl;
        return nullptr;
    }
}

void GameMap::addEnemy(EnemyType type, Vector<uint8_t> position) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for enemy");
        }
        auto enemy = entityFactory.createEnemy(entityCount, type, position);
        std::cout << "[GAMEMAP] Adding enemy at position: (" << static_cast<int>(position.x) << ", "
                  << static_cast<int>(position.y) << ")" << std::endl;
        entityCount++;
        addEntityToMap(enemy, position);
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding enemy: " << e.what() << std::endl;
    }
}

bool GameMap::isValidMapPosition(Vector<uint8_t> mapPosition) {
    return mapPosition.x >= 0 && mapPosition.x <= size.x && mapPosition.y >= 0 &&
           mapPosition.y <= size.y;
}

bool GameMap::isValidPosition(Vector<uint8_t> position) {
    return position.x >= 0 && position.x <= size.x * movesPerCell && position.y >= 0 &&
           position.y <= size.y * movesPerCell;
}

Vector<uint8_t> GameMap::getAvailablePosition() {
    try {
        Vector<uint8_t> pos;
        do {
            pos = {static_cast<uint8_t>(rand() % size.x), static_cast<uint8_t>(rand() % size.y)};
        } while (mapGrid.find(pos) != mapGrid.end() && isValidPosition(pos));
        return pos;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting available position: " << e.what() << std::endl;
        throw;
    }
}

void GameMap::update(float time) {
    std::cout << "[GAMEMAP] Updating game map" << std::endl;
    try {
        for (const auto& character: characters) {
            character.second->update(time);
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error updating game map: " << e.what() << std::endl;
    }
}

void GameMap::removeCharacter(uint8_t playerId) {
    try {
        auto character = characters[playerId];
        mapGrid.erase(character->getPosition());
        std::cout << "[GAMEMAP] Removed character with ID " << static_cast<int>(playerId)
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error removing character: " << e.what() << std::endl;
    }
}

void GameMap::removeEnemy(Vector<uint8_t> position) {
    try {
        mapGrid.erase(position);
        std::cout << "[GAMEMAP] Removed enemy at position: (" << static_cast<int>(position.x)
                  << ", " << static_cast<int>(position.y) << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error removing enemy: " << e.what() << std::endl;
    }
}

std::shared_ptr<Entity> GameMap::getEntityAt(Vector<uint8_t> mapPosition) {
    try {
        if (isValidPosition(mapPosition) && mapGrid.find(mapPosition) != mapGrid.end()) {
            return mapGrid[mapPosition];
        }
        return nullptr;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting entity at position: " << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<GameDTO> GameMap::getGameDTO() {
    std::cout << "[GAMEMAP] Creating GameDTO" << std::endl;
    std::vector<PlayerDTO> playersDTO;
    std::vector<EnemyDTO> enemies;
    std::vector<BulletDTO> bullets;
    std::vector<ItemDTO> items;
    std::vector<WeaponDTO> weapons;
    std::vector<TileDTO> tiles;

    try {
        for (const auto& character: characters) {
            playersDTO.push_back(character.second->getDTO());
            std::cout << "[GAMEMAP] Character added to DTO" << std::endl;
        }
        // for (const auto& [pos, entity]: mapGrid) {
        //     switch (entity->getType()) {
        //         // case EntityType::ENEMY:
        //         //     // enemies.push_back(std::dynamic_pointer_cast<Enemy>(entity)->getDTO());
        //         //     break;
        //         // case EntityType::BULLET:
        //         //     // bullets.push_back(std::dynamic_pointer_cast<Bullet>(entity)->getDTO());
        //         //     break;
        //         // case EntityType::ITEM:
        //         //     // items.push_back(std::dynamic_pointer_cast<Item>(entity)->getDTO());
        //         //     break;
        //         // case EntityType::TILE:
        //         //     // tiles.push_back(std::dynamic_pointer_cast<Tile>(entity)->getDTO());
        //         //     break;
        //         default:
        //             break;
        //     }
        // }
        std::cout << "[GAMEMAP] playersDTO size: " << playersDTO.size() << std::endl;

        return std::make_unique<GameDTO>(playersDTO, enemies, bullets, items, weapons, tiles);
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error creating GameDTO: " << e.what() << std::endl;
        throw;
    }
}

std::shared_ptr<Character> GameMap::getCharacter(uint8_t playerId) {
    try {
        return characters.at(playerId);
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting character with ID " << static_cast<int>(playerId)
                  << ": " << e.what() << std::endl;
        return nullptr;
    }
}

void GameMap::printMapGrid() const {
    try {
        for (const auto& pair: mapGrid) {
            std::cout << "[GAMEMAP] Key: (" << static_cast<int>(pair.first.x) << ", "
                      << static_cast<int>(pair.first.y) << "), "
                      << "Value: " << static_cast<int>(pair.second->getMapPosition(movesPerCell).x)
                      << ", " << static_cast<int>(pair.second->getMapPosition(movesPerCell).y)
                      << " - ID: " << static_cast<int>(pair.second->getId()) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error printing map grid: " << e.what() << std::endl;
    }
}

Vector<uint8_t> GameMap::getMapPosition(Vector<uint8_t> position) {
    return {static_cast<uint8_t>(position.x / movesPerCell),
            static_cast<uint8_t>(position.y / movesPerCell)};
}

Vector<uint8_t> GameMap::calculateNewPosition(const Vector<uint8_t> position, Direction dir) const {
    try {
        switch (dir) {
            case Direction::LEFT:
                return position.x - movesPerCell >= 0 ?
                               position - Vector<uint8_t>{movesPerCell, 0} :
                               position;
            case Direction::RIGHT:
                return position.x + movesPerCell <= size.x * movesPerCell ?
                               position + Vector<uint8_t>{movesPerCell, 0} :
                               position;
            case Direction::UP:
                return position.y + movesPerCell <= size.y * movesPerCell ?
                               position + Vector<uint8_t>{0, movesPerCell} :
                               position;
            case Direction::DOWN:
                return position.y - movesPerCell >= 0 ?
                               position - Vector<uint8_t>{0, movesPerCell} :
                               position;
            default:
                return position;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error calculating new position: " << e.what() << std::endl;
        throw;
    }
}

bool GameMap::handleMovement(Vector<uint8_t>& position, Vector<uint8_t> mapPosition,
                             const Vector<uint8_t>& newPosition,
                             const Vector<uint8_t>& newMapPosition) {
    try {
        if (newMapPosition == mapPosition) {
            std::cout << "[GAMEMAP] Same map position" << std::endl;
            return true;
        } else if (isFreePosition(newMapPosition)) {
            std::cout << "[GAMEMAP] Moving object to new position" << std::endl;
            mapGrid[newMapPosition] = mapGrid[mapPosition];
            mapGrid.erase(mapPosition);
            std::cout << "[GAMEMAP] Object at old position is nullptr: "
                      << (mapGrid.find(mapPosition) == mapGrid.end()) << std::endl;
            std::cout << "[GAMEMAP] Object old position: " << position << std::endl;
            position = newPosition;
            std::cout << "[GAMEMAP] Object new position: " << position << std::endl;
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error handling movement: " << e.what() << std::endl;
    }
    return false;
}
