#include "sprint.h"

SprintHandler::SprintHandler(std::unique_ptr<GameCommandDTO> sprintCommand):
        sprintCommand(std::move(sprintCommand)) {}

void SprintHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[SPRINT GAME HANDLER] Executing sprint command" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(sprintCommand->getPlayerId());

    if (!character) {
        std::cerr << "[SPRINT HANDLER] Character with ID "
                  << static_cast<int>(sprintCommand->getPlayerId())
                  << " not found. Skipping sprint command." << std::endl;
        return;
    }

    if (!character->isAlive()) {
        std::cerr << "[SPRINT HANDLER] Character with ID "
                  << static_cast<int>(sprintCommand->getPlayerId())
                  << " is dead. Skipping sprint command." << std::endl;
        return;
    } else {
        character->sprint(deltaTime);
    }
}