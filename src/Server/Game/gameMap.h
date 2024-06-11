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
    Vector<int16_t> size;
    std::map<Vector<int16_t>, std::shared_ptr<Entity>> mapGrid;
    std::map<int16_t, std::shared_ptr<Character>> characters;
    EntityFactory entityFactory;
    int16_t movesPerCell = 2;
    int16_t entityCount = 0;
    float gravity;

    Vector<int16_t> calculateNewPosition(const Vector<int16_t>& position, Direction dir) const;


    bool handleMovement(Vector<int16_t>& position, Vector<int16_t> mapPosition,
                        const Vector<int16_t>& newPosition, const Vector<int16_t>& newMapPosition);


public:
    explicit GameMap(Vector<int16_t> size);

    std::vector<std::shared_ptr<Entity>> getObjectsInShootRange(Vector<int16_t> mapPosition,
                                                                Direction dir);

    std::vector<std::shared_ptr<Entity>> getObjectsInExplosionRange(Vector<int16_t> mapPosition,
                                                                    int16_t radius);

    void moveObject(Vector<int16_t>& position, Vector<int16_t> mapPosition, Direction dir);

    Vector<int16_t> getAvailablePosition();

    void addEntityToMap(std::shared_ptr<Entity> entity, Vector<int16_t> position);

    std::shared_ptr<Character> addCharacter(uint32_t playerId, CharacterType type,
                                            std::optional<Vector<int16_t>> position);

    void addEnemy(EnemyType type, std::optional<Vector<int16_t>> position);

    void update(float time);

    void removeCharacter(uint32_t playerId);

    void removeEnemy(Vector<int16_t> position);

    std::shared_ptr<Entity> getEntityAt(Vector<int16_t> position);

    std::unique_ptr<GameDTO> getGameDTO();

    std::shared_ptr<Character> getCharacter(uint32_t playerId);

    bool isFreePosition(Vector<int16_t> position);

    bool isValidMapPosition(Vector<int16_t> mapPosition);

    bool isValidPosition(Vector<int16_t> position);

    void printMapGrid() const;

    Vector<int16_t> getMapPosition(Vector<int16_t> position, int16_t movesPerCell);
};

#endif  // GAME_MAP_H_
