#ifndef JUMPING_STATE_H_
#define JUMPING_STATE_H_

#include "state.h"
#include <utility> 
#include <memory>
#include "../../../Common/Types/move.h"

class JumpingState : public State {
public:
    JumpingState() {
        characterState = CharacterStateEntity::JUMPING;
    }

    std::unique_ptr<State> update(float time) override;
    std::unique_ptr<State> shoot(Character& character, 
    std::unique_ptr<Weapon> weapon, float time) override;
    std::unique_ptr<State> move(Character& character, Move direction, float time) override;
    std::unique_ptr<State> sprint(Character& character, float time) override;
    std::unique_ptr<State> reload(std::unique_ptr<Weapon> weapon, float time) override;
    std::unique_ptr<State> receiveDamage(Character& character, uint16_t dmg, float time) override;
    std::unique_ptr<State> die(Character& character, float time) override;
    std::unique_ptr<State> revive(Character& character, float time) override;
    std::unique_ptr<State> jump(Character& character, float time) override;
    std::unique_ptr<State> specialAttack(Character& character, float time) override;
    std::unique_ptr<State> becomeIntoxicated(Character& character, float duration) override;
    std::unique_ptr<State> stopAction() override;
};

#endif  // JUMPING_STATE_H_
