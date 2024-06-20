#include "startGame.h"

#include <atomic>
#include <memory>
#include <utility>

StartGameHandler::StartGameHandler(std::unique_ptr<StartGameDTO> command):
        command(std::move(command)) {}

void StartGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                               std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    uint8_t playerId = command->getPlayerId();
    uint8_t gameId = command->getGameId();
    gameMonitor.startGame(playerId, gameId, sendQueue);
    std::cout << "[SG HANDLER] Game started" << std::endl;
    inGame.store(true);
}