#ifndef STATE_H
#define STATE_H

#define CONFIG Configuration::getInstance()
#include "../config.h"
#include "../../../Common/Types/entity.h" 
#include <utility>
#include <cstdint>

class Weapon;
class Character;

class State {
public:
    virtual ~State() = default;

    virtual State* update(float time) = 0;
    virtual State* shoot(Character& character, Weapon* weapon, float time) = 0;
    virtual State* move(Character& character, Move direction, float time) = 0;
    virtual State* sprint(Character& character, float time) = 0;
    virtual State* reload(Weapon* weapon, float time) = 0;
    virtual State* receiveDamage(Character& character, uint16_t dmg, float time) = 0;
    virtual State* die(Character& character, float time) = 0;
    virtual State* revive(Character& character, float time) = 0;
    virtual State* jump(Character& character, float time) = 0;
    virtual State* specialAttack(Character& character, float time) = 0;
    virtual State* becomeIntoxicated(Character& character, float duration) = 0;
    virtual State* stopAction() = 0;

    CharacterState characterState = IDLE;
};


#endif // STATE_H
