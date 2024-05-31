#include "gamesList.h"

GamesListHandler::GamesListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

std::unique_ptr<LobbyDTO> GamesListHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    std::map<int32_t, std::string> games = gameMonitor.getGamesList();
    GamesListDTO gamesListDTO(games);
    LobbyDTO lobbyDTO(LobbyState::GAMES_LIST);
    lobbyDTO.setGamesList(gamesListDTO);
    return std::make_unique<LobbyDTO>(lobbyDTO);
}