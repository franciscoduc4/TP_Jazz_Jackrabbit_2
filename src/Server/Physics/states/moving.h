#ifndef MOVE_H
#define MOVE_H

#include <memory>
#include <utility>

#include "../../../Common/Types/direction.h"

#include "state.h"


class MovingState: public State {
private:
    Character& character;
    Direction direction;
    float time;

public:
    MovingState(Character& character, Direction direction, float time);

    std::unique_ptr<State> exec(Character& character, float time) override;
    std::unique_ptr<State> shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                 float time) override;
    std::unique_ptr<State> move(Character& character, Direction direction, float time) override;
    std::unique_ptr<State> reload(std::shared_ptr<Weapon> weapon, float time) override;
    std::unique_ptr<State> sprint(Character& character, Direction direction, float time) override;
    std::unique_ptr<State> receiveDamage(Character& character, uint16_t damage,
                                         float time) override;
    std::unique_ptr<State> die(Character& character, float respawnTime) override;
    std::unique_ptr<State> revive(Character& character, float time) override;
    std::unique_ptr<State> becomeIntoxicated(Character& character, float duration) override;
    std::unique_ptr<State> jump(Character& character, float time) override;
    std::unique_ptr<State> specialAttack(Character& character, float time) override;
    std::unique_ptr<State> stopAction() override;
};

#endif  // MOVE_H
