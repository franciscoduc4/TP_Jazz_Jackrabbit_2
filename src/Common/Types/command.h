#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>

enum class Command : char {
    IDLE,
    CREATE_GAME,
    JOIN_GAME,
    GAMES_LIST,
    EPISODES_LIST,
    GAME_MODE,
    CHARACTER_TYPE,
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
    INVALID
};

#endif  // COMMAND_H
