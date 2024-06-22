#include "shoot.h"

ShootHandler::ShootHandler(std::unique_ptr<CommandDTO> shootCommand):
        shootCommand(std::move(shootCommand)) {}

void ShootHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[SHOOT GAME HANDLER] Executing shoot command" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(shootCommand->getPlayerId());
    character->shoot(deltaTime);
}