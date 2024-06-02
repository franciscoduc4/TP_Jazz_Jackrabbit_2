#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <map>
#include <memory>
#include <vector>

#include "../../Common/Types/character.h"
#include "../../Common/Types/move.h"
#include "../../Common/Types/enemy.h"
#include "../../Common/vector.h"
#include "enemies/enemy.h"

#include "entity.h"
#include "entityFactory.h"
#include "playerCharacter.h"

class GameMap {
private:
    Vector<int16_t> size;
    std::map<Vector<int16_t>, std::shared_ptr<Entity>> mapGrid;
    std::vector<std::shared_ptr<Character>> characters;
    std::vector<std::shared_ptr<Enemy>> enemies;
    EntityFactory entityFactory;
    int16_t movesPerCell = 2;

    bool isFreePosition(Vector<int16_t> position);
    bool isValidPosition(Vector<int16_t> position);

public:
    explicit GameMap(Vector<int16_t> size);

    std::vector<std::shared_ptr<Entity>> getObjectsInShootRange(Vector<int16_t> mapPosition,
                                                                Move dir);

    std::vector<std::shared_ptr<Entity>> getObjectsInExplosionRange(Vector<int16_t> mapPosition,
                                                                    int16_t radius);

    void moveObject(Vector<int16_t>& position, Vector<int16_t> mapPosition, Move dir);

    Vector<int16_t> getAvailablePosition();

    std::shared_ptr<Character> addCharacter(CharacterType type);

    void addEnemy(EnemyType type);

    void update(float time);

 
};

#endif  // GAME_MAP_H_

