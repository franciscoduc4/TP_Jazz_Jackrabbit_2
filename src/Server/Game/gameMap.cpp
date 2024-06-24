#include "gameMap.h"

#include <iostream>
#include <optional>

#include "../../Common/maps/mapsManager.h"

// #define CONFIG ServerConfig::getInstance()

GameMap::GameMap(Vector<uint32_t> size, uint8_t mapId):
        size(size),
        entityFactory(*this),
        gravity(ServerConfig::getGameGravity()),
        movesPerCell(ServerConfig::getGameMaxMoves()),
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
        size.x = static_cast<uint32_t>(config["SIZE"]["WIDTH"].as<int>());
        size.y = static_cast<uint32_t>(config["SIZE"]["HEIGHT"].as<int>());
        std::cout << "[GAMEMAP] Map size: Width = " << static_cast<int>(size.x)
                  << ", Height = " << static_cast<int>(size.y) << std::endl;

        if (size.x <= 0 || size.y <= 0) {
            throw std::runtime_error("Map size must be positive non-zero values");
        }

        // Cargar obstáculos
        if (config["OBSTACLES"]) {
            for (const auto& obstacle: config["OBSTACLES"]) {
                std::string obstacleType = obstacle.first.as<std::string>();
                for (const auto& pos: obstacle.second) {
                    Vector<uint32_t> position = {static_cast<uint32_t>(pos[0].as<int>()),
                                                 static_cast<uint32_t>(pos[1].as<int>())};
                    uint32_t width = static_cast<uint32_t>(pos[2].as<int>());
                    uint32_t height = static_cast<uint32_t>(pos[3].as<int>());
                    ObstacleType type = getObstacleType(obstacleType);
                    addObstacle(type, position, width, height);
                    std::cout << "[GAMEMAP] Obstacle start position set for obstacleType: "
                              << obstacleType << " at (" << position.x << ", " << position.y
                              << "), width: " << width << ", height: " << height << std::endl;
                }
            }
        }
        // Cargar enemigos
        if (config["ENEMIES"]) {
            for (const auto& enemy: config["ENEMIES"]) {
                std::string enemyType = enemy.first.as<std::string>();
                std::cout << "[GAMEMAP] Enemy type: " << enemyType << std::endl;
                for (const auto& pos: enemy.second) {
                    if (pos.size() != 4) {
                        throw std::runtime_error(
                                "Invalid enemy position configuration in YAML file");
                    }
                    Vector<uint32_t> position = {static_cast<uint32_t>(pos[0].as<int>()),
                                                 static_cast<uint32_t>(pos[1].as<int>())};
                    uint32_t width = static_cast<uint32_t>(pos[2].as<int>());
                    uint32_t height = static_cast<uint32_t>(pos[3].as<int>());
                    EnemyType type = getEnemyType(enemyType);
                    addEnemy(type, position, width, height);
                    std::cout << "[GAMEMAP] Enemy position: (" << static_cast<int>(position.x)
                              << ", " << static_cast<int>(position.y) << "), width: " << width
                              << ", height: " << height << std::endl;
                }
            }
        }
        // Cargar ítems
        if (config["ITEMS"]) {
            for (const auto& item: config["ITEMS"]) {
                std::string itemTypeStr = item.first.as<std::string>();
                ItemType itemType = getItemType(itemTypeStr);  // Asegúrate de tener esta función
                for (const auto& pos: item.second) {
                    Vector<uint32_t> position = {static_cast<uint32_t>(pos[0].as<int>()),
                                                 static_cast<uint32_t>(pos[1].as<int>())};
                    uint32_t width = static_cast<uint32_t>(pos[2].as<int>());
                    uint32_t height = static_cast<uint32_t>(pos[3].as<int>());
                    addItem(itemType, position, width, height);
                    std::cout << "[GAMEMAP] Item start position set for itemType: " << itemTypeStr
                              << " at (" << position.x << ", " << position.y
                              << "), width: " << width << ", height: " << height << std::endl;
                }
            }
        }

        // Cargar posiciones iniciales de los personajes
        if (config["PLAYERS"]) {
            for (const auto& player: config["PLAYERS"]) {
                std::string playerType = player.first.as<std::string>();
                Vector<uint32_t> position = {static_cast<uint32_t>(player.second[0][0].as<int>()),
                                             static_cast<uint32_t>(player.second[0][1].as<int>())};
                uint32_t width = static_cast<uint32_t>(player.second[0][2].as<int>());
                uint32_t height = static_cast<uint32_t>(player.second[0][3].as<int>());
                CharacterType type = getCharacterType(playerType);
                initialPositions[type] = position;
                initialSizes[type] = {width, height};  // Guardar ancho y alto de los personajes
                std::cout << "[GAMEMAP] Initial position for character " << playerType << ": ("
                          << position.x << ", " << position.y << "), width: " << width
                          << ", height: " << height << std::endl;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error loading map: " << e.what() << std::endl;
        throw;
    }
}


ObstacleType GameMap::getObstacleType(const std::string& typeStr) {
    if (typeStr == "FULL_FLOOR")
        return ObstacleType::FULL_FLOOR;
    if (typeStr == "LEFT_LADDER")
        return ObstacleType::LEFT_LADDER;
    if (typeStr == "LONG_PLATFORM")
        return ObstacleType::LONG_PLATFORM;
    if (typeStr == "RIGHT_LADDER")
        return ObstacleType::RIGHT_LADDER;
    if (typeStr == "SMALL_PLATFORM")
        return ObstacleType::SMALL_PLATFORM;
    if (typeStr == "COLUMN")
        return ObstacleType::COLUMN;
    throw std::runtime_error("Unknown obstacle type: " + typeStr);
}

EnemyType GameMap::getEnemyType(const std::string& typeStr) {
    if (typeStr == "TURTLES")
        return EnemyType::TURTLE;
    if (typeStr == "YELLOWMONS")
        return EnemyType::YELLOWMON;
    if (typeStr == "SCHWARZENGUARDS")
        return EnemyType::SCHWARZENGUARD;
    throw std::runtime_error("Unknown enemy type: " + typeStr);
}

ItemType GameMap::getItemType(const std::string& typeStr) {
    if (typeStr == "FOOD")
        return ItemType::FOOD;
    if (typeStr == "GEMS")
        return ItemType::GEM;
    if (typeStr == "SILVER_COINS")
        return ItemType::SILVER_COIN;
    if (typeStr == "GOLD_COINS")
        return ItemType::GOLD_COIN;
    throw std::runtime_error("Unknown item type: " + typeStr);
}

CharacterType GameMap::getCharacterType(const std::string& typeStr) {
    if (typeStr == "JAZZ")
        return CharacterType::JAZZ;
    if (typeStr == "LORI")
        return CharacterType::LORI;
    if (typeStr == "SPAZ")
        return CharacterType::SPAZ;
    throw std::runtime_error("Unknown character type: " + typeStr);
}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInShootRange(Vector<uint32_t> mapPosition,
                                                                     Direction dir) {
    std::vector<std::shared_ptr<Entity>> entities;
    std::cout << "[GAMEMAP] Getting objects in shoot range" << std::endl;
    try {
        if (dir == Direction::LEFT) {
            for (int8_t i = mapPosition.x - 1; i >= 0; i--) {
                Vector<uint32_t> pos = {static_cast<uint8_t>(i), mapPosition.y};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        } else if (dir == Direction::RIGHT) {
            for (uint8_t i = mapPosition.x + 1; i < size.x; i++) {
                Vector<uint32_t> pos = {i, mapPosition.y};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error getting objects in shoot range: " << e.what() << std::endl;
    }
    std::cout << "[GAMEMAP] Objects in shoot range size: " << entities.size() << std::endl;
    return entities;
}

std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInExplosionRange(
        Vector<uint32_t> mapPosition, uint8_t radius) {
    std::vector<std::shared_ptr<Entity>> entities;
    try {
        for (int8_t i = mapPosition.x - radius; i <= mapPosition.x + radius; i++) {
            for (int8_t j = mapPosition.y - radius; j <= mapPosition.y + radius; j++) {
                Vector<uint32_t> pos = {static_cast<uint8_t>(i), static_cast<uint8_t>(j)};
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

void GameMap::moveObject(Vector<uint32_t>& position, Vector<uint32_t> mapPosition, Direction dir) {
    try {
        auto it = mapGrid.find(mapPosition);
        if (it == mapGrid.end()) {
            std::cerr << "[GAMEMAP] Invalid character at position: (" << mapPosition.x << ", "
                      << mapPosition.y << ")" << std::endl;
            return;
        }

        auto character = std::dynamic_pointer_cast<Character>(it->second);
        if (!character) {
            std::cerr << "[GAMEMAP] Character at (" << mapPosition.x << ", " << mapPosition.y
                      << ") is invalid" << std::endl;
            return;
        }

        Vector<uint32_t> newPosition = calculateNewPosition(position, dir);
        Vector<uint32_t> newMapPosition = getMapPosition(newPosition);
        if (!isValidMapPosition(newMapPosition)) {
            std::cerr << "[GAMEMAP] New map position (" << newMapPosition.x << ", "
                      << newMapPosition.y << ") is invalid" << std::endl;
            return;
        }

        if (mapGrid.find(newMapPosition) == mapGrid.end()) {
            mapGrid[newMapPosition] = it->second;
            mapGrid.erase(it);
            character->setPosition(newPosition);
            std::cout << "[GAMEMAP] Object moved from (" << mapPosition.x << ", " << mapPosition.y
                      << ") to (" << newMapPosition.x << ", " << newMapPosition.y << ")"
                      << std::endl;
        } else {
            character->interact(mapGrid[newMapPosition]);
        }

    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error moving object: " << e.what() << std::endl;
    }
}


bool GameMap::isFreePosition(Vector<uint32_t> position) {
    return mapGrid.find(position) == mapGrid.end();
}

void GameMap::addEntityToMap(std::shared_ptr<Entity> entity, Vector<uint32_t> position) {
    try {
        // Vector<uint32_t> mapPosition = entity->getMapPosition(movesPerCell);
        std::cout << "[GAMEMAP] Adding entity at position: (" << static_cast<int>(position.x)
                  << ", " << static_cast<int>(position.y) << ")" << std::endl;
        if (isFreePosition(position)) {
            mapGrid[position] = entity;
        } else {
            position = getAvailablePosition();
            mapGrid[position] = entity;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding entity to map: " << e.what() << std::endl;
    }
}

void GameMap::addCharacter(uint8_t playerId, CharacterType type) {
    try {
        auto it = initialPositions.find(type);
        if (it == initialPositions.end()) {
            std::cerr << "[GAMEMAP] Initial position for character type not found" << std::endl;
            return;
        }

        Vector<uint32_t> initPosition = it->second;
        Vector<uint32_t> initSize = initialSizes[type];  // Obtener el tamaño inicial del personaje
        std::cout << "[ADD CHARACTER] Initial position for character: ("
                  << static_cast<int>(initPosition.x) << ", " << static_cast<int>(initPosition.y)
                  << "), width: " << initSize.x << ", height: " << initSize.y << std::endl;

        if (!isValidMapPosition(initPosition)) {
            std::cerr << "[GAMEMAP] Invalid initial position for character" << std::endl;
            return;
        }

        auto character =
                entityFactory.createCharacter(playerId, type, initPosition, initSize.x, initSize.y);
        if (!character) {
            std::cerr << "[GAMEMAP] Failed to create character" << std::endl;
            return;
        }

        characters[playerId] = character;
        addEntityToMap(character, initPosition);
        entityCount++;
        std::cout << "[GAMEMAP] Character with ID " << static_cast<int>(playerId) << " added"
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding character: " << e.what() << std::endl;
        return;
    }
}


void GameMap::addEnemy(EnemyType type, Vector<uint32_t> position, uint32_t width, uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for enemy");
        }
        auto enemy = entityFactory.createEnemy(entityCount, type, position, width, height);
        std::cout << "[GAMEMAP] Adding enemy at position: (" << static_cast<int>(position.x) << ", "
                  << static_cast<int>(position.y) << "), width: " << width << ", height: " << height
                  << std::endl;
        enemies[enemy->getId()] = enemy;  // Añadir a la lista de enemigos
        addEntityToMap(enemy, position);
        entityCount++;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding enemy: " << e.what() << std::endl;
    }
}


void GameMap::addObstacle(ObstacleType type, Vector<uint32_t> position, uint32_t width,
                          uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for obstacle");
        }
        auto obstacle = entityFactory.createObstacle(type, position, width, height);
        std::cout << "[GAMEMAP] Adding obstacle at position: (" << static_cast<int>(position.x)
                  << ", " << static_cast<int>(position.y) << "), width: " << width
                  << ", height: " << height << std::endl;

        addEntityToMap(obstacle, position);
        entityCount++;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding obstacle: " << e.what() << std::endl;
    }
}

void GameMap::addItem(ItemType type, Vector<uint32_t> position, uint32_t width, uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for item");
        }
        auto item = entityFactory.createItem(type, position, width, height);
        std::cout << "[GAMEMAP] Adding item at position: (" << static_cast<int>(position.x) << ", "
                  << static_cast<int>(position.y) << "), width: " << width << ", height: " << height
                  << std::endl;
        addEntityToMap(item, position);
        entityCount++;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error adding item: " << e.what() << std::endl;
    }
}

bool GameMap::isValidMapPosition(Vector<uint32_t> mapPosition) {
    return mapPosition.x >= 0 && mapPosition.x <= size.x && mapPosition.y >= 0 &&
           mapPosition.y <= size.y;
}


bool GameMap::isValidPosition(Vector<uint32_t> position) {
    return position.x >= 0 && position.x < size.x * movesPerCell && position.y >= 0 &&
           position.y < size.y * movesPerCell;
}

Vector<uint32_t> GameMap::getAvailablePosition() {
    try {
        Vector<uint32_t> pos;
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
        for (const auto& characterPair: characters) {
            auto character = characterPair.second;
            character->update(time);

            // Verificar colisiones con entidades
            for (const auto& entityPair: mapGrid) {
                switch (entityPair.second->getType()) {
                    case EntityType::ENEMY:
                        handleCharacterEnemyCollision(
                                character, std::dynamic_pointer_cast<Enemy>(entityPair.second));
                        break;
                    case EntityType::OBSTACLE:
                        handleCharacterObstacleCollision(
                                character, std::dynamic_pointer_cast<Obstacle>(entityPair.second));
                        break;
                    case EntityType::ITEM:
                        handleCharacterItemCollision(
                                character, std::dynamic_pointer_cast<Item>(entityPair.second));
                        break;
                    default:
                        character->setOnGround(false);
                        break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error updating game map: " << e.what() << std::endl;
    }
}

bool GameMap::checkCollision(const Vector<uint32_t>& pos1, const Vector<uint32_t>& size1,
                             const Vector<uint32_t>& pos2, const Vector<uint32_t>& size2) {
    return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x &&
            pos1.y + size1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
}


void GameMap::handleCharacterItemCollision(std::shared_ptr<Character> character,
                                           std::shared_ptr<Item> item) {
    try {

        if (character->getPosition() == item->getPosition()) {
            character->collectItem(item);
            mapGrid.erase(item->getPosition());
            std::cout << "[GAMEMAP] Character collected item. Item removed from map." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error handling character-item collision: " << e.what() << std::endl;
    }
}

void GameMap::handleCharacterEnemyCollision(std::shared_ptr<Character> character,
                                            std::shared_ptr<Enemy> enemy) {

    try {
        if (character->getPosition() == enemy->getPosition()) {
            uint8_t damage = enemy->getDamage();  // Suponiendo que Enemy tiene un método
                                                  // getDamageValue()
            character->recvDamage(damage, 0);     // Llamar al método recvDamage del personaje
            character->handleCollision(enemy);    // Llamar al método handleCollision del personaje
            std::cout << "[GAMEMAP] Character ID: " << static_cast<int>(character->getId())
                      << " received damage from enemy. Damage: " << static_cast<int>(damage)
                      << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error handling character-enemy collision: " << e.what()
                  << std::endl;
    }
}

void GameMap::handleCharacterObstacleCollision(std::shared_ptr<Character> character,
                                               std::shared_ptr<Obstacle> obstacle) {
    try {
        auto characterPos = character->getPosition();
        auto characterWidth = character->getWidth();
        auto characterHeight = character->getHeight();

        auto obstaclePos = obstacle->getPosition();
        auto obstacleWidth = obstacle->getWidth();
        auto obstacleHeight = obstacle->getHeight();

        if (checkCollision(characterPos, {characterWidth, characterHeight}, obstaclePos,
                           {obstacleWidth, obstacleHeight})) {
            std::cout << "[GAMEMAP] Character ID: " << static_cast<int>(character->getId())
                      << " collided with obstacle" << std::endl;

            if (obstacle->getObstacleType() == ObstacleType::LEFT_LADDER ||
                obstacle->getObstacleType() == ObstacleType::RIGHT_LADDER) {
                character->handleLadderCollision(obstacle);
            } else {
                character->handleObstacleCollision(obstacle);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error handling character-obstacle collision: " << e.what()
                  << std::endl;
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

void GameMap::removeItem(Vector<uint32_t> position) {
    try {
        mapGrid.erase(position);
        std::cout << "[GAMEMAP] Removed item at position: (" << static_cast<int>(position.x) << ", "
                  << static_cast<int>(position.y) << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error removing item: " << e.what() << std::endl;
    }
}

void GameMap::removeEnemy(uint8_t enemyId) {
    try{ 
        auto it = enemies.find(enemyId);
        if (it != enemies.end()) {
            auto position = it->second->getPosition();
            mapGrid.erase(position);
            enemies.erase(it);
            std::cout << "[GAMEMAP] Removed enemy with ID: " << static_cast<int>(enemyId)
                    << " at position: (" << position.x << ", " << position.y << ")" << std::endl;
        } else {
            std::cerr << "[GAMEMAP] Error removing enemy: Enemy ID not found" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error removing enemy: " << e.what() << std::endl;
    }
}

std::shared_ptr<Entity> GameMap::getEntityAt(Vector<uint32_t> mapPosition) {
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
    std::vector<PlayerDTO> playersDTO;
    std::vector<EnemyDTO> enemiesDTO;
    std::vector<BulletDTO> bulletsDTO;
    std::vector<ItemDTO> itemsDTO;
    std::vector<WeaponDTO> weaponsDTO;
    std::vector<TileDTO> tilesDTO;

    try {

        for (const auto& [pos, entity]: mapGrid) {
            switch (entity->getType()) {
                case EntityType::CHARACTER:
                    playersDTO.push_back(std::dynamic_pointer_cast<Character>(entity)->getDTO());
                    break;
                case EntityType::ENEMY:
                    enemiesDTO.push_back(std::dynamic_pointer_cast<Enemy>(entity)->getDTO());
                    break;
                case EntityType::ITEM:
                    itemsDTO.push_back(std::dynamic_pointer_cast<Item>(entity)->getDTO());
                    break;

                case EntityType::OBSTACLE:
                    tilesDTO.push_back(std::dynamic_pointer_cast<Obstacle>(entity)->getDTO());
                    break;
                default:
                    std::cerr << "[GAMEMAP] Unknown entity type at position: (" << pos.x << ", "
                              << pos.y << ")" << std::endl;
                    break;
            }
        }

        std::cout << "[GAMEMAP] playersDTO size: " << playersDTO.size() << std::endl;
        std::cout << "[GAMEMAP] enemiesDTO size: " << enemiesDTO.size() << std::endl;
        std::cout << "[GAMEMAP] itemsDTO size: " << itemsDTO.size() << std::endl;
        std::cout << "[GAMEMAP] weaponsDTO size: " << weaponsDTO.size() << std::endl;
        std::cout << "[GAMEMAP] bulletsDTO size: " << bulletsDTO.size() << std::endl;
        std::cout << "[GAMEMAP] tilesDTO size: " << tilesDTO.size() << std::endl;

        return std::make_unique<GameDTO>(playersDTO, enemiesDTO, bulletsDTO, itemsDTO, weaponsDTO,
                                         tilesDTO);
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error creating GameDTO: " << e.what() << std::endl;
        throw;
    }
}

std::shared_ptr<Character> GameMap::getCharacter(uint8_t playerId) {
    std::cout << "[GAMEMAP] Getting character with ID " << (int)(playerId) << std::endl;
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

Vector<uint32_t> GameMap::getMapPosition(Vector<uint32_t> position) {
    // return {position.x / movesPerCell, position.y / movesPerCell};
    return {position.x, position.y};
}

Vector<uint32_t> GameMap::calculateNewPosition(const Vector<uint32_t> position,
                                               Direction dir) const {
    try {
        Vector<uint32_t> newPosition = position;
        switch (dir) {
            case Direction::LEFT:
                if (position.x >= movesPerCell) {
                    newPosition.x -= movesPerCell;
                }
                break;
            case Direction::RIGHT:
                if (position.x + movesPerCell < size.x * movesPerCell) {
                    newPosition.x += movesPerCell;
                }
                break;
            case Direction::UP:
                if (position.y + movesPerCell < size.y * movesPerCell) {
                    newPosition.y += movesPerCell;
                }
                break;
            case Direction::DOWN:
                if (position.y >= movesPerCell) {
                    newPosition.y -= movesPerCell;
                }
                break;
            default:
                break;
        }
        return newPosition;
    } catch (const std::exception& e) {
        std::cerr << "[GAMEMAP] Error calculating new position: " << e.what() << std::endl;
        throw;
    }
}
void GameMap::handleShooting(uint32_t characterX, uint8_t damage, float time, Direction dir) {
    const uint32_t shootRange = 100; // Define el alcance máximo del disparo
    std::cout << "[GAMEMAP] Handling shooting at position: " << characterX
              << ", damage: " << static_cast<int>(damage) << std::endl;
    
    std::vector<uint8_t> enemiesToRemove;
    std::cout << "[GAMEMAP] Number of enemies: " << enemies.size() << std::endl;

    for (const auto& enemyPair : enemies) {
        auto enemy = enemyPair.second;
        uint32_t enemyX = enemy->getPosition().x;
        std::cout << "[GAMEMAP] Checking enemy at position: " << enemyX << std::endl;

        bool inRange = false;
        if (dir == Direction::RIGHT) {
            if (enemyX >= characterX && enemyX <= characterX + shootRange) {
                inRange = true;
            }
        } else if (dir == Direction::LEFT) {
            if (enemyX <= characterX && enemyX >= characterX - shootRange) {
                inRange = true;
            }
        }

        if (inRange) {
            enemy->recvDamage(damage, time);
            std::cout << "[GAMEMAP] Enemy ID: " << static_cast<int>(enemy->getId())
                      << " received damage from shooting at x = " << characterX 
                      << " in direction " << (dir == Direction::RIGHT ? "RIGHT" : "LEFT")
                      << std::endl;
            
            if (enemy->isDead()) {
                enemiesToRemove.push_back(enemy->getId());
            }
        }
    }

    for (auto enemyId : enemiesToRemove) {
        removeEnemy(enemyId);
        std::cout << "[GAMEMAP] Enemy with ID " << static_cast<int>(enemyId) << " removed" << std::endl; 
    }
}
