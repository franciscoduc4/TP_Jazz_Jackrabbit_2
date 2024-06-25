#ifndef DAMAGE_STATE_H
#define DAMAGE_STATE_H

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"

#include "state.h"

class ReceivingDamageState: public State {
private:
    float startTime;
    float currentTime = 0;
    float timeReceivingDamage;
    uint8_t damage;
    Character& character;

public:
    explicit ReceivingDamageState(Character& character, float startTime, uint8_t damage);

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
    bool isReceivingDamage(float time) const;
};

#endif  // DAMAGE_STATE_H
