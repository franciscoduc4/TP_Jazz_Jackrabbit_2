#ifndef LOBBY_DTO_H_
#define LOBBY_DTO_H_

#include "../Types/lobbyState.h"

#include "gamesList.h"

class LobbyDTO {
private:
    bool gameCreated = false;
    bool gameJoined = false;
    bool gameStarted = false;

    GamesListDTO gamesList;

public:
    LobbyDTO(LobbyState state);
    bool getGameCreated() const;
    bool getGameJoined() const;
    bool getGameStarted() const;
    void setGamesList(GamesListDTO gamesList);
    GamesListDTO getGamesList() const;
};

#endif  // LOBBY_DTO_H_