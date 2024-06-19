#ifndef LOBBY_DTO_H_
#define LOBBY_DTO_H_

#include <memory>
#include "dto.h"

#include "../Types/lobbyState.h"

#include "gamesList.h"

class LobbyDTO : public DTO {
private:
    bool gameCreated = false;
    bool gameJoined = false;
    bool gameStarted = false;

    GamesListDTO gamesList;

    DTOType type = DTOType::LOBBY;

public:
    explicit LobbyDTO(LobbyState state);
    DTOType getType() const;
    bool getGameCreated() const;
    bool getGameJoined() const;
    bool getGameStarted() const;
    void setGamesList(GamesListDTO gamesList);
    GamesListDTO getGamesList() const;
    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // LOBBY_DTO_H_
