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
#include "../../Common/Types/enemy.h"
#include "../../Common/vector.h"
#include "characters/character.h"
#include "enemies/enemy.h"

#include "entity.h"
#include "entityFactory.h"

class GameMap {
private:
    Vector<uint8_t> size;
    std::map<Vector<uint8_t>, std::shared_ptr<Entity>> mapGrid;
    std::map<uint8_t, std::shared_ptr<Character>> characters;
    EntityFactory entityFactory;
    uint8_t entityCount;
    uint8_t movesPerCell;
    float gravity;
    std::string mapName;
    uint8_t mapId;


    Vector<uint8_t> calculateNewPosition(const Vector<uint8_t> position, Direction dir) const;


    bool handleMovement(Vector<uint8_t>& position, Vector<uint8_t> mapPosition,
                        const Vector<uint8_t>& newPosition, const Vector<uint8_t>& newMapPosition);


public:
    explicit GameMap(Vector<uint8_t> size, uint8_t mapId);

    void loadMap(uint8_t mapId);

    std::vector<std::shared_ptr<Entity>> getObjectsInShootRange(Vector<uint8_t> mapPosition,
                                                                Direction dir);

    std::vector<std::shared_ptr<Entity>> getObjectsInExplosionRange(Vector<uint8_t> mapPosition,
                                                                    uint8_t radius);

    void moveObject(Vector<uint8_t>& position, Vector<uint8_t> mapPosition, Direction dir);

    Vector<uint8_t> getAvailablePosition();

    void addEntityToMap(std::shared_ptr<Entity> entity, Vector<uint8_t> position);

    std::shared_ptr<Character> addCharacter(uint8_t playerId, CharacterType type);

    void addEnemy(EnemyType type, Vector<uint8_t> position);

    void update(float time);

    void removeCharacter(uint8_t playerId);

    void removeEnemy(Vector<uint8_t> position);

    std::shared_ptr<Entity> getEntityAt(Vector<uint8_t> position);

    std::unique_ptr<GameDTO> getGameDTO();

    std::shared_ptr<Character> getCharacter(uint8_t playerId);

    bool isFreePosition(Vector<uint8_t> position);

    bool isValidMapPosition(Vector<uint8_t> mapPosition);

    bool isValidPosition(Vector<uint8_t> position);

    void printMapGrid() const;

    Vector<uint8_t> getMapPosition(Vector<uint8_t> position);

    Vector<uint8_t> getInitialPositionForCharacterType(CharacterType type);


    EnemyType getEnemyType(const std::string& type);
};

#endif  // GAME_MAP_H_
