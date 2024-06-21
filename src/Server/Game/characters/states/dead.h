#ifndef DEAD_STATE_H_
#define DEAD_STATE_H_

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"
#include "../../../../Common/Types/entity.h"
#include "../character.h"

#include "state.h"


class DeadState: public State {
private:
    float reviveTime;
    float startTime;
    Character& character;

public:
    explicit DeadState(Character& character, float time);

    std::unique_ptr<State> exec(float time) override;
    std::unique_ptr<State> shoot(const std::shared_ptr<Weapon>& weapon, float time) override;
    std::unique_ptr<State> move(Direction direction, float time) override;
    std::unique_ptr<State> sprint(Direction direction, float time) override;
    std::unique_ptr<State> receiveDamage(uint8_t dmg, float time) override;
    std::unique_ptr<State> die(float time) override;
    std::unique_ptr<State> revive(float time) override;
    std::unique_ptr<State> jump(float time) override;
    std::unique_ptr<State> specialAttack(float time) override;
    std::unique_ptr<State> becomeIntoxicated(float duration) override;
    std::unique_ptr<State> stopAction() override;

    bool canRevive(float time) const;
};

#endif  // DEAD_STATE_H_
