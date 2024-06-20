#include "gamesList.h"

#include <map>
#include <string>
#include <utility>

GamesListHandler::GamesListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

void GamesListHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                               std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    gameMonitor.gamesList(sendQueue);
}
