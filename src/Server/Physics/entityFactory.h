#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <cstdint>
#include <vector>

#include "enemies/enemy.h"

#include "gameMap.h"

class EntityFactory {
private:
public:
    std::shared_ptr<Jazz> createJazz(Vector<int16_t> position) {}
    std::shared_ptr<Spaz> createSpaz(Vector<int16_t> position) {}
    std::shared_ptr<Lori> createLori(Vector<int16_t> position) {}
    std::shared_ptr<Enemy> createWalker(Vector<int16_t> position) {}
    std::shared_ptr<Enemy> createFlyer(Vector<int16_t> position) {}
    std::shared_ptr<Enemy> createJumper(Vector<int16_t> position) {}
};


#endif  // ENTITY_FACTORY_H_
