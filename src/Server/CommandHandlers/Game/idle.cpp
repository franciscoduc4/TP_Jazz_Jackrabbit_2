#include "idle.h"

#include "../../../Common/DTO/command.h"

IdleHandler::IdleHandler(std::unique_ptr<CommandDTO> idleCommand):
        idleCommand(std::move(idleCommand)) {}

void IdleHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[IDLE HANDLER] Executing idle command" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(idleCommand->getPlayerId());
    character->idle(deltaTime);
    std::cout << "[IDLE HANDLER] Idle command executed" << std::endl;
}