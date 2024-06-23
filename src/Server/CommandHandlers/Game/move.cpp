#include "move.h"

#include "gameCommand.h"

MoveHandler::MoveHandler(std::unique_ptr<GameCommandDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

void MoveHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    switch (moveCommand->getMoveType()) {
        case Direction::UP:
            std::cout << "[MOVE HANDLER] Moving character up" << std::endl;
            character->moveUp(deltaTime);
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
            // character->idle(deltaTime);
            break;
    }
}