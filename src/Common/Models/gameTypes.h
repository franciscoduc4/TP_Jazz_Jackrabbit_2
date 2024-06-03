#ifndef GAME_TYPES_H_
#define GAME_TYPES_H_

#include "vector.h"

namespace GameTypes {

enum class ActionType { MOVE, SHOOT, JUMP };

struct Action {
    ActionType type;
    int playerId;
    float direction;        // Used for MOVE
    float currentTime;      // Used for SHOOT
    Vector shootDirection;  // Used for SHOOT
};

}  // namespace GameTypes

#endif  // GAME_TYPES_H_
