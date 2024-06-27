#include "gameMap.h"

#include <array>
#include <cstdlib>
#include <iostream>
#include <optional>

#include "../../Common/maps/mapsManager.h"


#include "../../Common/printer.h"

GameMap::GameMap(Vector<uint32_t> size, uint8_t mapId):
        size(size),
        entityFactory(*this),
        gravity(ServerConfig::getGameGravity()),
        entityCount(0),
        movesPerCell(ServerConfig::getGameMaxMoves()),
        mapId(mapId) {
    // std::cout << "[GAMEMAP] GameMap created with mapId: " << static_cast<int>(mapId) <<
    // std::endl;
    enemies_respawn_time[EnemyType::TURTLE] = ServerConfig::getTurtleEnemyRespawnTime();
    enemies_respawn_time[EnemyType::YELLOWMON] = ServerConfig::getYellowmonsEnemyRespawnTime();
    enemies_respawn_time[EnemyType::SCHWARZENGUARD] = ServerConfig::getSchwarzenguardEnemyRespawnTime();
    enemies_cooldown_respawn[EnemyType::TURTLE] = 0;
    enemies_cooldown_respawn[EnemyType::YELLOWMON] = 0;
    enemies_cooldown_respawn[EnemyType::SCHWARZENGUARD] = 0;
}

/*
 * Carga un mapa a partir de su ID.
 * Lee el archivo YAML correspondiente y carga las configuraciones de tamaño, obstáculos, enemigos, ítems y posiciones iniciales de los personajes.
 */
void GameMap::loadMap(uint8_t mapId) {
    try {
        std::string filePath = MapsManager::getMapFileNameById(mapId);
        YAML::Node config = YAML::LoadFile(filePath);

        if (!config["SIZE"] || !config["SIZE"]["WIDTH"] || !config["SIZE"]["HEIGHT"]) {
            throw std::runtime_error("Invalid map size configuration in YAML file");
        }
        size.x = static_cast<uint32_t>(config["SIZE"]["WIDTH"].as<int>());
        size.y = static_cast<uint32_t>(config["SIZE"]["HEIGHT"].as<int>());

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
                }
            }
        }

        // Cargar enemigos
        if (config["ENEMIES"]) {
            for (const auto& enemy: config["ENEMIES"]) {
                auto enemyType = enemy.first.as<std::string>();
                for (const auto& pos: enemy.second) {
                    if (pos.size() != 4) {
                        throw std::runtime_error("Invalid enemy position configuration in YAML file");
                    }
                    Vector<uint32_t> position = {static_cast<uint32_t>(pos[0].as<int>()),
                                                 static_cast<uint32_t>(pos[1].as<int>())};
                    uint32_t width = static_cast<uint32_t>(pos[2].as<int>());
                    uint32_t height = static_cast<uint32_t>(pos[3].as<int>());
                    EnemyType type = getEnemyType(enemyType);
                    addEnemy(type, position, width, height);
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
                initialSizes[type] = {width, height};
            }
        }

    } catch (const std::exception& e) {
        throw;
    }
}

/*
 * Devuelve el tipo de obstáculo a partir de su nombre.
 */
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

/*
 * Devuelve el tipo de enemigo a partir de su nombre.
 */
EnemyType GameMap::getEnemyType(const std::string& typeStr) {
    if (typeStr == "TURTLES")
        return EnemyType::TURTLE;
    if (typeStr == "YELLOWMONS")
        return EnemyType::YELLOWMON;
    if (typeStr == "SCHWARZENGUARDS")
        return EnemyType::SCHWARZENGUARD;
    throw std::runtime_error("Unknown enemy type: " + typeStr);
}

/*
 * Devuelve el tipo de ítem a partir de su nombre.
 */
ItemType GameMap::getItemType(const std::string& typeStr) {
    if (typeStr == "FOOD")
        return ItemType::FOOD;
    if (typeStr == "GEMS")
        return ItemType::GEM;
    if (typeStr == "SILVER_COINS")
        return ItemType::SILVER_COIN;
    if (typeStr == "GOLD_COINS")
        return ItemType::GOLD_COIN;
    if (typeStr == "POISONED_FOOD")
        return ItemType::POISONED_FOOD;
    if (typeStr == "BULLET")
        return ItemType::BULLET;
    throw std::runtime_error("Unknown item type: " + typeStr);
}

/*
 * Devuelve el tipo de carácter a partir de su nombre.
 */
CharacterType GameMap::getCharacterType(const std::string& typeStr) {
    if (typeStr == "JAZZ")
        return CharacterType::JAZZ;
    if (typeStr == "LORI")
        return CharacterType::LORI;
    if (typeStr == "SPAZ")
        return CharacterType::SPAZ;
    throw std::runtime_error("Unknown character type: " + typeStr);
}

/*
 * Devuelve las entidades dentro del rango de disparo de una posición y dirección dadas.
 */
std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInShootRange(Vector<uint32_t> mapPosition, Direction dir) {
    std::vector<std::shared_ptr<Entity>> entities;
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
        // Error al obtener objetos en rango de disparo
    }
    return entities;
}

// Método para obtener entidades en un área definida
std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInAreaRange(Vector<uint32_t> mapPosition, uint32_t range) {
    std::vector<std::shared_ptr<Entity>> entities;
    try {
        for (uint32_t x = mapPosition.x - range; x <= mapPosition.x + range; ++x) {
            for (uint32_t y = mapPosition.y - range; y <= mapPosition.y + range; ++y) {
                Vector<uint32_t> pos = {x, y};
                if (mapGrid.find(pos) != mapGrid.end()) {
                    entities.push_back(mapGrid[pos]);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error getting objects in area range: " << e.what() << std::endl;
    }
    return entities;
}


// Método para obtener entidades en un rango vertical
std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInVerticalRange(Vector<uint32_t> mapPosition, uint32_t range) {
    std::vector<std::shared_ptr<Entity>> entities;
    try {
        for (uint32_t i = mapPosition.y - range; i <= mapPosition.y + range; ++i) {
            Vector<uint32_t> pos = {mapPosition.x, i};
            if (mapGrid.find(pos) != mapGrid.end()) {
                entities.push_back(mapGrid[pos]);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error getting objects in vertical range: " << e.what() << std::endl;
    }
    return entities;
}

/*
 * Devuelve las entidades dentro del rango de explosión de una posición y radio dados.
 */
std::vector<std::shared_ptr<Entity>> GameMap::getObjectsInExplosionRange(Vector<uint32_t> mapPosition, uint8_t radius) {
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
        // Error al obtener objetos en rango de explosión
    }
    return entities;
}

/*
 * Mueve un objeto de una posición a otra en una dirección dada.
 */
void GameMap::moveObject(Vector<uint32_t>& position, Vector<uint32_t> mapPosition, Direction dir) {
    try {
        auto it = mapGrid.find(mapPosition);
        if (it == mapGrid.end()) {
            return;
        }

        auto character = std::dynamic_pointer_cast<Character>(it->second);
        if (!character) {
            return;
        }

        Vector<uint32_t> newPosition = calculateNewPosition(position, dir);
        Vector<uint32_t> newMapPosition = getMapPosition(newPosition);
        if (!isValidMapPosition(newMapPosition)) {
            return;
        }

        if (mapGrid.find(newMapPosition) == mapGrid.end()) {
            mapGrid[newMapPosition] = it->second;
            mapGrid.erase(it);
            character->setPosition(newPosition);
        }

    } catch (const std::exception& e) {
        // Error al mover objeto
    }
}

/*
 * Verifica si una posición está libre.
 */
bool GameMap::isFreePosition(Vector<uint32_t> position) {
    return mapGrid.find(position) == mapGrid.end();
}

/*
 * Agrega una entidad al mapa en una posición dada.
 */
void GameMap::addEntityToMap(std::shared_ptr<Entity> entity, Vector<uint32_t> position) {
    try {
        if (isFreePosition(position)) {
            mapGrid[position] = entity;
        } else {
            position = getAvailablePosition();
            mapGrid[position] = entity;
        }
    } catch (const std::exception& e) {
        // Error al agregar entidad al mapa
    }
}

/*
 * Agrega un personaje al mapa.
 */
void GameMap::addCharacter(uint8_t playerId, CharacterType type) {
    try {
        auto it = initialPositions.find(type);
        if (it == initialPositions.end()) {
            return;
        }

        Vector<uint32_t> initPosition = it->second;
        Vector<uint32_t> initSize = initialSizes[type];

        if (!isValidMapPosition(initPosition)) {
            return;
        }

        auto character = entityFactory.createCharacter(playerId, type, initPosition, initSize.x, initSize.y);
        if (!character) {
            return;
        }

        characters[playerId] = character;
        addEntityToMap(character, initPosition);
        entityCount++;
    } catch (const std::exception& e) {
        // Error al agregar personaje
    }
}

/*
 * Agrega un enemigo al mapa en una posición dada.
 */
void GameMap::addEnemy(EnemyType type, Vector<uint32_t> position, uint32_t width, uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for enemy");
        }
        auto enemy = entityFactory.createEnemy(entityCount, type, position, width, height);
        if (enemy == nullptr) {
            throw std::runtime_error("Failed to create enemy");
        }
        uint8_t enemyId = enemy->getId();
        enemies[enemyId] = enemy;
        addEntityToMap(enemy, position);
        entityCount++;
    } catch (const std::exception& e) {
        // Error al agregar enemigo
    }
}

/*
 * Agrega un obstáculo al mapa en una posición dada.
 */
void GameMap::addObstacle(ObstacleType type, Vector<uint32_t> position, uint32_t width, uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for obstacle");
        }
        auto obstacle = entityFactory.createObstacle(type, position, width, height);
        addEntityToMap(obstacle, position);
        entityCount++;
    } catch (const std::exception& e) {
        // Error al agregar obstáculo
    }
}

/*
 * Agrega un ítem al mapa en una posición dada.
 */
void GameMap::addItem(ItemType type, Vector<uint32_t> position, uint32_t width, uint32_t height) {
    try {
        if (!isValidMapPosition(position)) {
            throw std::runtime_error("Invalid position for item");
        }
        auto item = entityFactory.createItem(type, position, width, height);
        addEntityToMap(item, position);
        entityCount++;
        Printer::printDebugHighlightedMessage("EL ENTITY COUNE TIENE UN VALOR");
        std::cout << static_cast<int>(entityCount) << '\n'; 
    } catch (const std::exception& e) {
        // Error al agregar ítem
    }
}

/*
 * Verifica si una posición del mapa es válida.
 */
bool GameMap::isValidMapPosition(Vector<uint32_t> mapPosition) {
    return mapPosition.x >= 0 && mapPosition.x <= size.x && mapPosition.y >= 0 && mapPosition.y <= size.y;
}

/*
 * Verifica si una posición es válida.
 */
bool GameMap::isValidPosition(Vector<uint32_t> position) {
    return position.x >= 0 && position.x < size.x * movesPerCell && position.y >= 0 && position.y < size.y * movesPerCell;
}

/*
 * Devuelve una posición disponible en el mapa.
 */
Vector<uint32_t> GameMap::getAvailablePosition() {
    try {
        Vector<uint32_t> pos;
        do {
            pos = {static_cast<uint8_t>(rand() % size.x), static_cast<uint8_t>(rand() % size.y)};
        } while (mapGrid.find(pos) != mapGrid.end() && isValidPosition(pos));
        return pos;
    } catch (const std::exception& e) {
        // Error al obtener posición disponible
        throw;
    }
}

/*
 * Actualiza el estado del mapa del juego.
 */
void GameMap::update(float time) {
    try {
        std::vector<std::shared_ptr<Entity>> entitiesToRemove;
        std::vector<std::shared_ptr<Entity>> itemsToRemove;

        for (auto& entityPair: mapGrid) {
            auto entity = entityPair.second;

            if (entity->getType() == EntityType::CHARACTER) {
                auto character = std::dynamic_pointer_cast<Character>(entity);
                character->update(time);
                if (!character->isAlive()) {
                    continue;
                }

                for (const auto& checkEntityPair: mapGrid) {
                    auto checkEntity = checkEntityPair.second;
                    switch (checkEntity->getType()) {
                        case EntityType::ENEMY:
                            handleCharacterEnemyCollision(character, std::dynamic_pointer_cast<Enemy>(checkEntity));
                            break;
                        case EntityType::OBSTACLE:
                            handleCharacterObstacleCollision(character, std::dynamic_pointer_cast<Obstacle>(checkEntity));
                            break;
                        case EntityType::ITEM:
                            if (handleCharacterItemCollision(character, std::dynamic_pointer_cast<Item>(checkEntity))) {
                                itemsToRemove.push_back(std::dynamic_pointer_cast<Item>(checkEntity));
                            }
                            break;
                        default:
                            character->setOnGround(false);
                            break;
                    }
                }
            } else if (entity->getType() == EntityType::ENEMY) {
                auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
                enemy->update(characters, time);
            } else if (entity->getType() == EntityType::ITEM) {
                auto item = std::dynamic_pointer_cast<Item>(entity);
                item->update(time);
            }
        }

        for (const auto& entity: entitiesToRemove) {
            removeCharacter(std::dynamic_pointer_cast<Character>(entity));
        }

        for (const auto& entity: itemsToRemove) {
            removeItem(entity->getPosition());
            collected_items.push_back(std::dynamic_pointer_cast<Item>(entity));
        }
        std::vector<std::shared_ptr<Item>>::iterator it_items = collected_items.begin();
        if (it_items != collected_items.end() && collected_items.size() > ServerConfig::getItemsCollected()) {
            collected_items.erase(it_items);
            addItem((*it_items)->getItemType(), (*it_items)->getPosition(), (*it_items)->getWidth(), (*it_items)->getHeight());
        }
        std::map<EnemyType, std::vector<std::shared_ptr<Enemy>>>::iterator it = dead_enemies.begin();
        while (it != dead_enemies.end()) {
            enemies_cooldown_respawn[it->first] += enemies_respawn_time[it->first] / 5;
            if (enemies_cooldown_respawn[it->first] >= enemies_respawn_time[it->first]) {
                enemies_cooldown_respawn[it->first] = 0;
                if (it->second.size() > 2) {
                    Printer::printDebugHighlightedMessage("LA CANTIDAD DE ENEMIGOS MUERTOS ES");
                    std::cout << it->second.size() << '\n';
                    addEnemy(it->second[0]->getEnemyType(), it->second[0]->getPosition(), it->second[0]->getWidth(), it->second[0]->getHeight());
                    it->second.erase(it->second.begin());
                }
            }
            it++;
        }

    } catch (const std::exception& e) {
        // Error al actualizar el mapa del juego
    }
}

/*
 * Verifica si hay colisión entre dos posiciones y tamaños dados.
 */
bool GameMap::checkCollision(const Vector<uint32_t>& pos1, const Vector<uint32_t>& size1, const Vector<uint32_t>& pos2, const Vector<uint32_t>& size2) {
    return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x && pos1.y + size1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
}

/*
 * Maneja la colisión entre un personaje y un ítem.
 */
bool GameMap::handleCharacterItemCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Item>& item) {
    try {
        if (checkCollision(character->getPosition(), {character->getWidth(), character->getHeight()}, item->getPosition(), {item->getWidth(), item->getHeight()})) {
            character->collectItem(item);
            std::cout << "[GAMEMAP] Character collected item. Item removed from map." << std::endl;
            return true;
        }
    } catch (const std::exception& e) {
        // Error al manejar colisión entre personaje e ítem
    }
    return false;
}

/*
 * Maneja la colisión entre un personaje y un enemigo.
 */
void GameMap::handleCharacterEnemyCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Enemy>& enemy) {
    try {
        if (!character->isAlive())
            return;

        if (checkCollision(character->getPosition(), {character->getWidth(), character->getHeight()}, enemy->getPosition(), {enemy->getWidth(), enemy->getHeight()})) {
            uint8_t damage = enemy->getDamage();
            character->recvDamage(damage, 0);
            character->handleEnemyCollision(enemy);
        }
    } catch (const std::exception& e) {
        // Error al manejar colisión entre personaje y enemigo
    }
}

/*
 * Maneja la colisión entre un personaje y un obstáculo.
 */
void GameMap::handleCharacterObstacleCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Obstacle>& obstacle) {
    try {
        auto characterPos = character->getPosition();
        auto characterWidth = character->getWidth();
        auto characterHeight = character->getHeight();

        auto obstaclePos = obstacle->getPosition();
        auto obstacleWidth = obstacle->getWidth();
        auto obstacleHeight = obstacle->getHeight();

        if (checkCollision(characterPos, {characterWidth, characterHeight}, obstaclePos, {obstacleWidth, obstacleHeight})) {
            if (obstacle->getObstacleType() == ObstacleType::LEFT_LADDER || obstacle->getObstacleType() == ObstacleType::RIGHT_LADDER) {
                character->handleLadderCollision(obstacle);
            } else {
                character->handleObstacleCollision(obstacle);
            }
        }
    } catch (const std::exception& e) {
        // Error al manejar colisión entre personaje y obstáculo
    }
}

/*
 * Elimina un personaje del mapa por su ID.
 */
void GameMap::removeCharacter(uint8_t playerId) { removeCharacter(getCharacter(playerId)); }

/*
 * Elimina un personaje del mapa.
 */
void GameMap::removeCharacter(const std::shared_ptr<Character>& character) {
    try {
        auto it = characters.find(character->getId());
        if (it != characters.end()) {
            auto position = it->second->getPosition();
            mapGrid.erase(position);
            characters.erase(it);
        } else {
            // Error al eliminar personaje: ID no encontrado
        }

    } catch (const std::exception& e) {
        // Error al eliminar personaje del mapa
    }
}

/*
 * Elimina un ítem del mapa en una posición dada.
 */
void GameMap::removeItem(Vector<uint32_t> position) {
    try {
        mapGrid.erase(position);
    } catch (const std::exception& e) {
        // Error al eliminar ítem
    }
}

/*
 * Elimina un enemigo del mapa por su ID.
 */
void GameMap::removeEnemy(uint8_t enemyId) {
    try {
        auto it = enemies.find(enemyId);
        if (it != enemies.end()) {
            auto position = it->second->getPosition();
            mapGrid.erase(position);
            enemies.erase(it);

            ItemType droppedItem = it->second->dropRandomItem();
            addItem(droppedItem, position, 1, 1);
        } else {
            // Error al eliminar enemigo: ID no encontrado
        }
    } catch (const std::exception& e) {
        // Error al eliminar enemigo
    }
}

/*
 * Devuelve la entidad en una posición dada.
 */
std::shared_ptr<Entity> GameMap::getEntityAt(Vector<uint32_t> mapPosition) {
    try {
        if (isValidPosition(mapPosition) && mapGrid.find(mapPosition) != mapGrid.end()) {
            return mapGrid[mapPosition];
        }
        return nullptr;
    } catch (const std::exception& e) {
        // Error al obtener entidad en posición dada
        return nullptr;
    }
}

/*
 * Devuelve el estado actual del juego en forma de GameDTO.
 */
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
                    break;
            }
        }
        return std::make_unique<GameDTO>(playersDTO, enemiesDTO, bulletsDTO, itemsDTO, weaponsDTO, tilesDTO);
    } catch (const std::exception& e) {
        // Error al crear GameDTO
        throw;
    }
}

/*
 * Devuelve el personaje con el ID dado.
 */
std::shared_ptr<Character> GameMap::getCharacter(uint8_t playerId) {
    auto it = characters.find(playerId);
    if (it != characters.end()) {
        return it->second;
    }
    // Error al obtener personaje con ID dado: personaje no encontrado
    return nullptr;
}

/*
 * Devuelve la posición en el mapa correspondiente a una posición dada.
 */
Vector<uint32_t> GameMap::getMapPosition(Vector<uint32_t> position) {
    return {position.x, position.y};
}

/*
 * Calcula la nueva posición en base a la dirección dada.
 */
Vector<uint32_t> GameMap::calculateNewPosition(const Vector<uint32_t>& position, Direction dir) const {
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
        // Error al calcular nueva posición
        throw;
    }
}

/*
 * Maneja el disparo de un personaje.
 */
void GameMap::handleShooting(uint32_t characterX, uint8_t damage, float time, Direction dir, uint8_t shooterId) {
    const uint32_t shootRange = ServerConfig::getGameMapShootRange();
    const uint32_t heightRange = ServerConfig::getGameMapHeightRange();

    std::vector<uint8_t> enemiesToRemove;

    auto shooter = characters[shooterId];
    if (!shooter) {
        std::cerr << "[GAMEMAP] Shooter character not found: ID " << static_cast<int>(shooterId) << std::endl;
        return;
    }
    uint32_t shooterY = shooter->getPosition().y;

    // Verificar enemigos
    for (const auto& enemyPair: enemies) {
        auto enemy = enemyPair.second;
        uint32_t enemyX = enemy->getPosition().x;
        uint32_t enemyY = enemy->getPosition().y;

        bool inRange = (dir == Direction::RIGHT && enemyX >= characterX && enemyX <= characterX + shootRange) ||
                       (dir == Direction::LEFT && enemyX <= characterX && enemyX >= characterX - shootRange);
        bool inHeightRange = (std::abs(static_cast<int>(enemyY) - static_cast<int>(shooterY)) <= heightRange);

        if (inRange && inHeightRange) {
            enemy->recvDamage(damage, time);
            std::cout << "[GAMEMAP] Enemy with ID: " << static_cast<int>(enemy->getId()) << " received damage: " << static_cast<int>(damage) << std::endl;
            if (enemy->isDead()) {
                uint32_t points = enemy->getPointsValue();
                std::cout << "[GAMEMAP] Enemy with ID: " << static_cast<int>(enemy->getId()) << " is dead. Points collected: " << static_cast<int>(enemy->getPointsValue()) << std::endl;
                enemiesToRemove.push_back(enemy->getId());
                shooter->collectPointsForEnemy(points);
                dead_enemies[enemy->getEnemyType()].push_back(std::dynamic_pointer_cast<Enemy>(enemy));
            }
        } else {
            std::cout << "[GAMEMAP] Enemy with ID: " << static_cast<int>(enemy->getId()) << " out of range. Enemy position: (" << enemyX << ", " << enemyY << ")" << std::endl;
        }
    }

    for (const auto& characterPair: characters) {
        auto character = characterPair.second;
        uint32_t characterXPos = character->getPosition().x;
        uint32_t characterYPos = character->getPosition().y;

        // No dispararse a sí mismo
        if (character->getId() == shooterId) {
            continue;
        }

        bool inRange = (dir == Direction::RIGHT && characterXPos >= characterX && characterXPos <= characterX + shootRange) ||
                       (dir == Direction::LEFT && characterXPos <= characterX && characterXPos >= characterX - shootRange);
        bool inHeightRange = (std::abs(static_cast<int>(characterYPos) - static_cast<int>(shooterY)) <= heightRange);

        if (inRange && inHeightRange) {
            character->recvDamage(damage, time);
            if (!character->isAlive()) {
                character->setState(std::make_unique<DeadState>(*character, time));
            }
            std::cout << "[GAMEMAP] Character with ID: " << static_cast<int>(character->getId()) << " received damage: " << static_cast<int>(damage) << std::endl;
        } else {
            std::cout << "[GAMEMAP] Character with ID: " << static_cast<int>(character->getId()) << " out of range. Character position: (" << characterXPos << ", " << characterYPos << ")" << std::endl;
        }
    }

    for (uint8_t id: enemiesToRemove) {
        removeEnemy(id);
        std::cout << "EL VALOR DEL ID ES " << static_cast<int>(id) << '\n';
        Printer::printDebugHighlightedMessage("SE ELIMINO UN ENEMIGO");
                
    }
}

/*
 * Resetea los puntajes de todos los personajes.
 */
void GameMap::resetScores() {
    for (auto& characterPair: characters) {
        auto character = characterPair.second;
        character->resetScore();
    }
}
