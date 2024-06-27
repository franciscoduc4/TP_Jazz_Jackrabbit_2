#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "../../Common/Config/ServerConfig.h"
#include "../../Common/DTO/game.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/obstacles.h"
#include "../../Common/Types/item.h"
#include "../../Common/Types/enemy.h"
#include "../../Common/vector.h"
#include "characters/character.h"
#include "enemies/enemy.h"
#include "items/item.h"
#include "obstacles/obstacle.h"
#include "entity.h"
#include "entityFactory.h"

class GameMap {
private:
    Vector<uint32_t> size;
    std::map<Vector<uint32_t>, std::shared_ptr<Entity>> mapGrid;
    std::map<uint8_t, std::shared_ptr<Character>> characters;
    std::map<uint8_t, std::shared_ptr<Enemy>> enemies;
    std::map<uint8_t, std::shared_ptr<Item>> items;
    std::map<uint8_t, std::shared_ptr<Obstacle>> obstacles;
    std::map<CharacterType, Vector<uint32_t>> initialPositions;
    std::map<CharacterType, Vector<uint32_t>> initialSizes;

    std::vector<std::shared_ptr<Enemy>> dead_enemies;
    std::vector<std::shared_ptr<Item>> collected_items;
    

    EntityFactory entityFactory;
    uint8_t entityCount;
    uint8_t movesPerCell;
    float gravity;
    std::string mapName;
    uint8_t mapId;

    Vector<uint32_t> calculateNewPosition(const Vector<uint32_t>& position, Direction dir) const;

public:
    explicit GameMap(Vector<uint32_t> size, uint8_t mapId);

    void loadMap(uint8_t mapId);

    std::vector<std::shared_ptr<Entity>> getObjectsInShootRange(Vector<uint32_t> mapPosition,
                                                                Direction dir);

    std::vector<std::shared_ptr<Entity>> getObjectsInExplosionRange(Vector<uint32_t> mapPosition,
                                                                    uint8_t radius);

    void moveObject(Vector<uint32_t>& position, Vector<uint32_t> mapPosition, Direction dir);

    Vector<uint32_t> getAvailablePosition();

    void addEntityToMap(std::shared_ptr<Entity> entity, Vector<uint32_t> position);

    void addCharacter(uint8_t playerId, CharacterType type);
    void addEnemy(EnemyType type, Vector<uint32_t> position, uint32_t width, uint32_t height);
    void addObstacle(ObstacleType type, Vector<uint32_t> position, uint32_t width, uint32_t height);
    void addItem(ItemType type, Vector<uint32_t> position, uint32_t width, uint32_t height);


    bool handleCharacterItemCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Item>& item);
    void handleCharacterEnemyCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Enemy>& enemy);
    void handleCharacterObstacleCollision(const std::shared_ptr<Character>& character, const std::shared_ptr<Obstacle>& obstacle);

    void handleShooting(uint32_t characterX, uint8_t damage, float time, Direction dir, uint8_t shooterId);
    bool checkCollision(const Vector<uint32_t>& pos1, const Vector<uint32_t>& size1, const Vector<uint32_t>& pos2, const Vector<uint32_t>& size2);

    void update(float time);
    void updateBullets(float time);

    void removeCharacter(uint8_t playerId);
    void removeCharacter(const std::shared_ptr<Character>& character);
    void removeEnemy(uint8_t enemyId);
    void removeItem(Vector<uint32_t> position);

    std::shared_ptr<Entity> getEntityAt(Vector<uint32_t> position);

    std::unique_ptr<GameDTO> getGameDTO();

    std::shared_ptr<Character> getCharacter(uint8_t playerId);

    bool isFreePosition(Vector<uint32_t> position);

    bool isValidMapPosition(Vector<uint32_t> mapPosition);

    bool isValidPosition(Vector<uint32_t> position);

    void printMapGrid() const;

    Vector<uint32_t> getMapPosition(Vector<uint32_t> position);



    EnemyType getEnemyType(const std::string& typeStr);
    ObstacleType getObstacleType(const std::string& typeStr);
    ItemType getItemType(const std::string& typeStr);
    CharacterType getCharacterType(const std::string& typeStr);

    uint32_t getMaxXPos() const { return size.x - static_cast<uint32_t>(movesPerCell); }

    uint32_t getMaxYPos() const { return size.y - static_cast<uint32_t>(movesPerCell); } 
};

#endif  // GAME_MAP_H_
