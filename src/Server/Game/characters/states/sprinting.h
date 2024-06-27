#ifndef SPRINT_H
#define SPRINT_H

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"

#include "state.h"


class SprintingState: public State {
private:
    Character& character;
    Direction direction;
    float waitingTime = 0.1f;
    float lastTime = 0.1f * -1;

public:
    SprintingState(Character& character, Direction direction);

    std::unique_ptr<State> exec(float time) override;
    std::unique_ptr<State> shoot(const std::shared_ptr<Weapon>& weapon, float time) override;
    std::unique_ptr<State> sprint(Direction direction2, float time) override;
    std::unique_ptr<State> move(Direction direction2, float time) override;
    std::unique_ptr<State> receiveDamage(uint8_t dmg, float time) override;
    std::unique_ptr<State> die(float time) override;
    std::unique_ptr<State> revive(float time) override;
    std::unique_ptr<State> jump(float time) override;
    std::unique_ptr<State> specialAttack(float time) override;
    std::unique_ptr<State> becomeIntoxicated(float duration) override;
    std::unique_ptr<State> stopAction() override;
};

#endif  // SPRINT_H
