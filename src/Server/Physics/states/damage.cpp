#include "damage.h"
#include "idle.h"
#include "move.h"
#include "dead.h"
#include "intoxicated.h"
#include "jumping.h"
#include "shooting.h"
#include "../playerCharacter.h"

ReceivingDamageState::ReceivingDamageState(float startTime) : 
    startTime(startTime),
    stopDamageTime(1) //CONFIG.getDamageTime();
    {
        characterState = CharacterState::TAKING_DAMAGE;
    }

State* ReceivingDamageState::update(float time) {
    if (time - startTime >= stopDamageTime) {
        return new IdleState();  
    }
    return nullptr;
}

State* ReceivingDamageState::shoot(Character& character, Weapon* weapon, float time) {
    if (time - startTime >= stopDamageTime) {
        return new ShootingState(character, weapon, time);  
    }
    return nullptr;
}

State* ReceivingDamageState::move(Character& character, Move direction, float time) {
    if (time - startTime >= stopDamageTime) {
        return new MoveState(character, direction, time);  
    }
    return nullptr;
}

State* ReceivingDamageState::reload(Weapon* weapon, float time) {
    return new IdleState();
}

State* ReceivingDamageState::receiveDamage(Character& character, uint16_t damage, float time) {
    startTime = time;
    return nullptr;
}

State* ReceivingDamageState::die(Character& character, float respawnTime) {
    return new DeadState(respawnTime);
}

State* ReceivingDamageState::becomeIntoxicated(Character& character, float duration) {
    return nullptr;
}

State* ReceivingDamageState::jump(Character& character, float time) {
    return nullptr;
}

State* ReceivingDamageState::stopAction() {
    return nullptr;
}

State* ReceivingDamageState::revive(Character& character, float time) {
    return nullptr;
}

