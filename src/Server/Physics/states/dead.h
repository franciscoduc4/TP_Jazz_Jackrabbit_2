#ifndef DEAD_STATE_H_
#define DEAD_STATE_H_

#include "state.h"
#include <utility> 
class DeadState : public State {
public:
    DeadState() {
        characterState = CharacterState::DEAD;
    }

    State* update(float time) override;
    State* shoot(Character& character, Weapon* weapon, float time) override;
    State* move(Character& character, std::int16_t direction, float time) override;
    State* sprint(Character& character, float time) override;
    State* reload(Weapon* weapon, float time) override;
    State* receiveDamage(Character& character, uint16_t dmg, float time) override;
    State* die(Character& character, float time) override;
    State* revive(Character& character, float time) override;
    State* jump(Character& character, float time) override;
    State* specialAttack(Character& character, float time) override;
    State* becomeIntoxicated(Character& character, float duration) override;
    State* stopAction() override;
};

#endif  // DEAD_STATE_H_
