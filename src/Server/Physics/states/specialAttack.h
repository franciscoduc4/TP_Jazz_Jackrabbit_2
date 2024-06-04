#ifndef SPECIAL_ATTACK_STATE_H_
#define SPECIAL_ATTACK_STATE_H_

#include <memory>
#include <utility>

#include "../../../Common/Types/direction.h"

#include "state.h"

class SpecialAttackState: public State {
private:
    float startTime;
    float duration;

public:
    explicit SpecialAttackState(float time);

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
};

#endif  // SPECIAL_ATTACK_STATE_H_
