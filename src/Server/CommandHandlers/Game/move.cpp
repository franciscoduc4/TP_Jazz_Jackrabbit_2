#include "move.h"

#include "gameCommand.h"

MoveHandler::MoveHandler(std::unique_ptr<GameCommandDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

void MoveHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
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

    switch (moveCommand->getMoveType()) {
        case Direction::UP:
            std::cout << "[MOVE HANDLER] Moving character up" << std::endl;
            character->jump(deltaTime);
            break;
        case Direction::DOWN:
            std::cout << "[MOVE HANDLER] Moving character down" << std::endl;
            character->moveDown(deltaTime);
            break;
        case Direction::LEFT:
            std::cout << "[MOVE HANDLER] Moving character left" << std::endl;
            character->moveLeft(deltaTime);
            break;
        case Direction::RIGHT:
            std::cout << "[MOVE HANDLER] Moving character right" << std::endl;
            character->moveRight(deltaTime);
            break;
        default:
            break;
    }
}