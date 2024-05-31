#ifndef LOBBY_STATE_H_
#define LOBBY_STATE_H_

enum class LobbyState : char {
    GAME_CREATED,
    GAME_NOT_CREATED,
    GAME_JOINED,
    GAME_NOT_JOINED,
    GAME_STARTED,
    GAME_NOT_STARTED,
    GAMES_LIST,
};

#endif  // LOBBY_STATE_H_