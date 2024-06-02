#include "idle.h"
#include "running.h"
#include "jumping.h"
#include "shooting.h"
#include "specialAttack.h"
#include "intoxicated.h"
#include "dead.h"

IdleState::IdleState() {
    characterState = IDLE;
}

State* IdleState::update(float time) {
    return this;
}

State* IdleState::shoot(Character& character, Weapon* weapon, float time) {
    if (weapon->isEmpty() || !weapon->shootTime(time)) {
        return this;
    }
    return new ShootingState(character, weapon, time);
}

State* IdleState::move(Character& character, Move direction, float time) {
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return new RunningState(direction);
}

State* IdleState::sprint(Character& character, float time) {
    character.sprint(time);
    return new RunningState(character.getDir());
}

State* IdleState::reload(Weapon* weapon, float time) {

    return this;
}

State* IdleState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* IdleState::die(Character& character, float time) {
    character.die(time);
    return new DeadState(time);
}

State* IdleState::revive(Character& character, float time) {

    return this;
}

State* IdleState::jump(Character& character, float time) {
    character.jump(time);
    return new JumpingState();
}

State* IdleState::specialAttack(Character& character, float time) {
    return new SpecialAttackState();
}

State* IdleState::becomeIntoxicated(Character& character, float duration) {
    return new IntoxicatedState(duration);
}

State* IdleState::stopAction() {
    return this;
}
