#ifndef SPECIAL_ATTACK_STATE_H_
#define SPECIAL_ATTACK_STATE_H_

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"

#include "state.h"

class SpecialAttackState: public State {
private:
    float startTime;
    float duration;
    Character& character;

public:
    SpecialAttackState(Character& character, float time);

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
};

#endif  // SPECIAL_ATTACK_STATE_H_
