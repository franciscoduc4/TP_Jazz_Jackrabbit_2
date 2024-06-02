#ifndef STATE_H
#define STATE_H

#define CONFIG Configuration::getInstance()
#include "../config.h"
#include "../../../Common/Types/entity.h" 
#include <utility>
#include <cstdint>
#include <memory>

class Weapon;
class Character;

class State {
public:
    virtual ~State() = default;

    virtual std::unique_ptr<State> update(float time) = 0;
    virtual std::unique_ptr<State> shoot(Character& character, 
    std::unique_ptr<Weapon> weapon, float time) = 0;
    virtual std::unique_ptr<State> move(Character& character, Move direction, float time) = 0;
    virtual std::unique_ptr<State> sprint(Character& character, float time) = 0;
    virtual std::unique_ptr<State> reload(std::unique_ptr<Weapon> weapon, float time) = 0;
    virtual std::unique_ptr<State> receiveDamage(Character& character, uint16_t dmg, float time) = 0;
    virtual std::unique_ptr<State> die(Character& character, float time) = 0;
    virtual std::unique_ptr<State> revive(Character& character, float time) = 0;
    virtual std::unique_ptr<State> jump(Character& character, float time) = 0;
    virtual std::unique_ptr<State> specialAttack(Character& character, float time) = 0;
    virtual std::unique_ptr<State> becomeIntoxicated(Character& character, float duration) = 0;
    virtual std::unique_ptr<State> stopAction() = 0;

    CharacterStateEntity characterState = IDLE;
};

#endif // STATE_H
