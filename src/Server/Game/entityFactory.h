#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/enemy.h"
#include "enemies/flyingEnemy.h"
#include "enemies/jumpingEnemy.h"
#include "enemies/walkingEnemy.h"

#include "gameMap.h"

class Jazz;
class Spaz;
class Lori;
class WalkingEnemy;
class FlyingEnemy;
class JumpingEnemy;

class EntityFactory {
private:
public:
    // std::shared_ptr<Jazz> createJazz(Vector<int16_t> position) { return std::make_shared<Jazz>();
    // } std::shared_ptr<Spaz> createSpaz(Vector<int16_t> position) { return
    // std::make_shared<Spaz>(); } std::shared_ptr<Lori> createLori(Vector<int16_t> position) {
    // return std::make_shared<Lori>(); }

    // std::shared_ptr<WalkingEnemy> createWalker(Vector<int16_t> position) {
    //     return std::make_shared<WalkingEnemy>();
    // }
    // std::shared_ptr<FlyingEnemy> createFlyer(Vector<int16_t> position) {
    //     return std::make_shared<FlyingEnemy>();
    // }
    // std::shared_ptr<JumpingEnemy> createJumper(Vector<int16_t> position) {
    //     return std::make_shared<JumpingEnemy>();
    // }
};


#endif  // ENTITY_FACTORY_H_
