#include "move.h"

MoveHandler::MoveHandler(std::unique_ptr<MoveDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

void MoveHandler::execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = game.getCharacter(moveCommand->getPlayerId());
    switch (moveCommand->getMoveType()) {
        case Direction::UP:
            character->moveUp(deltaTime);
            break;
        case Direction::DOWN:
            character->moveDown(deltaTime);
            break;
        case Direction::LEFT:
            character->moveLeft(deltaTime);
            break;
        case Direction::RIGHT:
            character->moveRight(deltaTime);
            break;
        default:
            break;
    }
}