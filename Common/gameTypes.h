#ifndef GAME_TYPES_H
#define GAME_TYPES_H

namespace GameTypes {
enum class Action {
    SHOOT = 0,
    RUN = 1,
    FAST_RUN = 2,
    JUMP = 3,
    TOXIC = 4,
};

enum class Event {
    PLAYER_DIED = 0,
    PLAYER_WON = 1,
    PLAYER_DISCONNECTED = 2,
    PLAYER_CONNECTED = 3,
    GAME_STARTED = 4,
    GAME_ENDED = 5,
};
}  // namespace GameTypes


#endif  // GAME_TYPES_H