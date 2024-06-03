#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "enemies/enemy.h"
#include "enemies/walkingEnemy.h"

#include "gameMap.h"

class Jazz;
class Spaz;
class Lori;
class Enemy;

class EntityFactory {
private:
public:
    // std::shared_ptr<Jazz> createJazz(Vector<int16_t> position) { return std::make_shared<Jazz>();
    // } std::shared_ptr<Spaz> createSpaz(Vector<int16_t> position) { return
    // std::make_shared<Spaz>(); } std::shared_ptr<Lori> createLori(Vector<int16_t> position) {
    // return std::make_shared<Lori>(); } std::shared_ptr<Enemy> createWalker(Vector<int16_t>
    // position) {
    //     return std::make_shared<Enemy>();
    // }
    // std::shared_ptr<Enemy> createFlyer(Vector<int16_t> position) {
    //     return std::make_shared<Enemy>();
    // }
    // std::shared_ptr<Enemy> createJumper(Vector<int16_t> position) {
    //     return std::make_shared<Enemy>();
    // }
};


#endif  // ENTITY_FACTORY_H_
