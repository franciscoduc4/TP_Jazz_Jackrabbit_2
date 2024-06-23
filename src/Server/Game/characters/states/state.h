#ifndef STATE_H
#define STATE_H
#include <cstdint>
#include <memory>
#include <utility>

#include "../../../../Common/Types/entity.h"

class Weapon;
class Character;

class State {
protected:
    bool onGround = false;

public:
    virtual ~State() = default;

    virtual std::unique_ptr<State> exec(float time) = 0;
    virtual std::unique_ptr<State> shoot(const std::shared_ptr<Weapon>& weapon, float time) = 0;
    virtual std::unique_ptr<State> move(Direction direction, float time) = 0;
    virtual std::unique_ptr<State> sprint(Direction direction, float time) = 0;
    virtual std::unique_ptr<State> receiveDamage(uint8_t dmg, float time) = 0;
    virtual std::unique_ptr<State> die(float time) = 0;
    virtual std::unique_ptr<State> revive(float time) = 0;
    virtual std::unique_ptr<State> jump(float time) = 0;
    virtual std::unique_ptr<State> specialAttack(float time) = 0;
    virtual std::unique_ptr<State> becomeIntoxicated(float duration) = 0;
    virtual std::unique_ptr<State> stopAction() = 0;
    CharacterStateEntity characterState = IDLE;

    virtual CharacterStateEntity getCharacterState() { return characterState; }
    virtual void setOnGround(bool onGround) { this->onGround = onGround; }
};

#endif  // STATE_H
