#ifndef DAMAGE_STATE_H
#define DAMAGE_STATE_H

#include <memory>
#include <utility>

#include "../../../Common/Types/direction.h"

#include "state.h"

class ReceivingDamageState: public State {
private:
    float startTime;
    float timeReceivingDamage;
    uint16_t damage;

public:
    explicit ReceivingDamageState(float startTime);

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
    bool isReceivingDamage(float time);
};

#endif  // DAMAGE_STATE_H
