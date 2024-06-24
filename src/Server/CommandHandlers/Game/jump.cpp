#include "jump.h"

JumpHandler::JumpHandler(std::unique_ptr<CommandDTO> jumpCommand):
        moveCommand(std::move(jumpCommand)) {}

void JumpHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    if (!character) {
        std::cerr << "[MOVE HANDLER] Character with ID " << static_cast<int>(moveCommand->getPlayerId())
                  << " not found. Skipping move command." << std::endl;
        return;
    }

    if (!character->isAlive()) {
        std::cerr << "[MOVE HANDLER] Character with ID " << static_cast<int>(moveCommand->getPlayerId())
                  << " is dead. Skipping move command." << std::endl;
        return;
    }
    else {
        //character->jump(deltaTime);
    }
}