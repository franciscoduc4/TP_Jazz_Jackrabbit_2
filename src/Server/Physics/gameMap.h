#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <map>
#include <memory>
#include <vector>

#include "../../Common/Types/character.h"
#include "../../Common/vector.h"

#include "entity.h"
#include "playerCharacter.h"

class GameMap {
private:
    Vector<int16_t> size;
    std::map<Vector<int16_t>, Entity> mapGrid;
    std::vector<std::shared_ptr<Character>> characters;
    // std::vector<std::shared_ptr<Enemy>> enemies;
    // GameCreator ver despues

public:
    GameMap(Vector<int16_t> size);

    void getObjectsInShootRange(Vector<int16_t> mapPosition, int16_t dir,
                                std::vector<Entity*>& entities);

    void getObjectsInExplosionRange(Vector<int16_t> mapPosition, float radius,
                                    std::vector<Entity*>& entities);

    void moveObject(Vector<int16_t> deltaPosition, Entity& entity);

    void getEntityPosition(Vector<int16_t> mapPosition);

    std::shared_ptr<Character> addCharacter(CharacterType type);
};

#endif  // GAME_MAP_H_