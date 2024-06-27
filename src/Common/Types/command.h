#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>

enum class Command : char {
    IDLE,
    CREATE_GAME,
    JOIN_GAME,
    GAMES_LIST,
    MAPS_LIST,
    GAME_MODE,
    CHARACTER_TYPE,
    GAME_UPDATE,
    START_GAME,
    SHOOT,
    SWITCH_WEAPON,
    MOVE,
    SPRINT,
    JUMP,
    INTOXICATED,
    TAKE_DAMAGE,
    DEATH,
    REVIVE,
    HEAL,
    UPPERCUT,
    SHORT_KICK,
    SIDE_KICK,
    CHEAT,
    SPECIAL_ATTACK,
    INVALID
};

#endif  // COMMAND_H
