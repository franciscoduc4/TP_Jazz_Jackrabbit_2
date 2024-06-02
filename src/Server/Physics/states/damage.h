#ifndef DAMAGE_STATE_H
#define DAMAGE_STATE_H

#include "state.h"
#include <utility>
#include "../../../Common/Types/move.h"

class ReceivingDamageState : public State {
private:
    float startTime;
    float stopDamageTime;

public:
    explicit ReceivingDamageState(float startTime);

    State* update(float time) override;
    State* shoot(Character& character, Weapon* weapon, float time) override;
    State* move(Character& character, Move direction, float time) override;
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

#endif // DAMAGE_STATE_H
