#include "gamesList.h"

#include <map>
#include <string>
#include <utility>

GamesListHandler::GamesListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

std::unique_ptr<CommandDTO> GamesListHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
        std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue) {
    std::map<uint32_t, GameInfo> games = gameMonitor.getGamesList();
    return std::make_unique<GamesListDTO>(games);
}
