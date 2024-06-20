#include "move.h"

#include "gameCommand.h"

MoveHandler::MoveHandler(std::unique_ptr<GameCommandDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

void MoveHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    switch (moveCommand->getMoveType()) {
        case Direction::UP:
            std::cout << "[MOVE HANDLER] Moving character up" << std::endl;
            character->update(Direction::UP);
            break;
        case Direction::DOWN:
            std::cout << "[MOVE HANDLER] Moving character down" << std::endl;
            // character->update(Direction::DOWN);
            break;
        case Direction::LEFT:
            std::cout << "[MOVE HANDLER] Moving character left" << std::endl;
            character->update(Direction::LEFT);
            break;
        case Direction::RIGHT:
            std::cout << "[MOVE HANDLER] Moving character right" << std::endl;
            character->update(Direction::RIGHT);
            break;
        default:
            break;
    }
}