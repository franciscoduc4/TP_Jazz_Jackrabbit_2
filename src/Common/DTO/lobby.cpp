#include "lobby.h"

LobbyDTO::LobbyDTO(LobbyState state) {
    if (state == LobbyState::GAME_CREATED) {
        gameCreated = true;
        gameJoined = false;
        gameStarted = false;
    } else if (state == LobbyState::GAME_NOT_CREATED) {
        gameCreated = false;
        gameJoined = false;
        gameStarted = false;
    } else if (state == LobbyState::GAME_JOINED) {
        gameCreated = true;
        gameJoined = true;
        gameStarted = false;
    } else if (state == LobbyState::GAME_NOT_JOINED) {
        gameCreated = true;
        gameJoined = false;
        gameStarted = false;
    } else if (state == LobbyState::GAME_STARTED) {
        gameCreated = true;
        gameJoined = true;
        gameStarted = true;
    } else if (state == LobbyState::GAME_NOT_STARTED) {
        gameCreated = true;
        gameJoined = true;
        gameStarted = false;
    }
    gamesList = GamesListDTO();
}

bool LobbyDTO::getGameCreated() const { return gameCreated; }

bool LobbyDTO::getGameJoined() const { return gameJoined; }

bool LobbyDTO::getGameStarted() const { return gameStarted; }

void LobbyDTO::setGamesList(GamesListDTO gamesList) { this->gamesList = gamesList; }

GamesListDTO LobbyDTO::getGamesList() const { return gamesList; }
