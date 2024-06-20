#ifndef SHOOTING_STATE_H_
#define SHOOTING_STATE_H_

#include <memory>
#include <utility>

#include "../../../../Common/Types/direction.h"
#include "../../weapons/weapon.h"

#include "state.h"

class ShootingState: public State {
private:
    Character& character;
    std::shared_ptr<Weapon> weapon;
    float startTime = -1;
    float waitToShoot;

public:
    ShootingState(Character& character, const std::shared_ptr<Weapon>& weapon, float time);

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

#endif  // SHOOTING_STATE_H_
