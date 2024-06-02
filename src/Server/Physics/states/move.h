#ifndef MOVE_H
#define MOVE_H

#include "state.h"
#include <utility>
#include "../../../Common/Types/move.h"


class MoveState : public State {
private:
    Character& character;
    Move direction; 
    float time;

public:
    MoveState(Character& character, Move direction, float time);

    State* update(float time) override;
    State* shoot(Character& character, Weapon* weapon, float time) override;
    State* move(Character& character, Move direction, float time) override;
    State* reload(Weapon* weapon, float time) override;
    State* sprint(Character& character, float time) override;
    State* receiveDamage(Character& character, uint16_t damage, float time) override;
    State* die(Character& character, float respawnTime) override;
    State* revive(Character& character, float time) override;
    State* becomeIntoxicated(Character& character, float duration) override;
    State* jump(Character& character, float time) override;
    State* specialAttack(Character& character, float time) override;
    State* stopAction() override;
};

#endif // MOVE_H
