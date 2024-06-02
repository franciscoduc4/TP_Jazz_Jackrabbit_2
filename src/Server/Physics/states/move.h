#ifndef MOVE_H
#define MOVE_H

#include "state.h"
#include <utility>
#include <memory>
#include "../../../Common/Types/move.h"


class MoveState : public State {
private:
    Character& character;
    Move direction; 
    float time;

public:
    MoveState(Character& character, Move direction, float time);

    std::unique_ptr<State> update(float time) override;
    std::unique_ptr<State> shoot(Character& character, 
    std::unique_ptr<Weapon> weapon, float time) override;
    std::unique_ptr<State> move(Character& character, Move direction, float time) override;
    std::unique_ptr<State> reload(std::unique_ptr<Weapon> weapon, float time) override;
    std::unique_ptr<State> sprint(Character& character, float time) override;
    std::unique_ptr<State> receiveDamage(Character& character, uint16_t damage, float time) override;
    std::unique_ptr<State> die(Character& character, float respawnTime) override;
    std::unique_ptr<State> revive(Character& character, float time) override;
    std::unique_ptr<State> becomeIntoxicated(Character& character, float duration) override;
    std::unique_ptr<State> jump(Character& character, float time) override;
    std::unique_ptr<State> specialAttack(Character& character, float time) override;
    std::unique_ptr<State> stopAction() override;
};

#endif // MOVE_H
