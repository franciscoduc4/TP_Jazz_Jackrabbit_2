#include "shoot.h"

ShootHandler::ShootHandler(std::unique_ptr<CommandDTO> shootCommand):
        shootCommand(std::move(shootCommand)) {}

void ShootHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[SHOOT GAME HANDLER] Executing shoot command" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(shootCommand->getPlayerId());

    if (!character) {
        std::cerr << "[MOVE HANDLER] Character with ID " << static_cast<int>(shootCommand->getPlayerId())
                  << " not found. Skipping move command." << std::endl;
        return;
    }

    if (!character->isAlive()) {
        std::cerr << "[MOVE HANDLER] Character with ID " << static_cast<int>(shootCommand->getPlayerId())
                  << " is dead. Skipping move command." << std::endl;
        return;
    }
    else {
        character->shoot(deltaTime);
    }
}