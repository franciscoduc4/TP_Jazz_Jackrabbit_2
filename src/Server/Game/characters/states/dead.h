#ifndef DEAD_STATE_H_
#define DEAD_STATE_H_

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"
#include "../../../../Common/Types/entity.h"

#include "state.h"


class DeadState: public State {
private:
    float reviveTime;
    float startTime;

public:
    explicit DeadState(float time);

    std::unique_ptr<State> exec(Character& character, float time) override;
    std::unique_ptr<State> shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                 float time) override;
    std::unique_ptr<State> move(Character& character, Direction direction, float time) override;
    std::unique_ptr<State> sprint(Character& character, Direction direction, float time) override;
    std::unique_ptr<State> receiveDamage(Character& character, uint16_t dmg, float time) override;
    std::unique_ptr<State> die(Character& character, float time) override;
    std::unique_ptr<State> revive(Character& character, float time) override;
    std::unique_ptr<State> jump(Character& character, float time) override;
    std::unique_ptr<State> specialAttack(Character& character, float time) override;
    std::unique_ptr<State> becomeIntoxicated(Character& character, float duration) override;
    std::unique_ptr<State> stopAction() override;

    bool canRevive(float time);
};

#endif  // DEAD_STATE_H_
