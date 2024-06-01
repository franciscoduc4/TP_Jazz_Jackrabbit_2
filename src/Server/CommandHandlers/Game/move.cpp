#include "move.h"

MoveHandler::MoveHandler(std::unique_ptr<MoveDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

void MoveHandler::execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = game.getCharacter(moveCommand->getPlayerId());
    switch (moveCommand->getMoveType()) {
        case Move::UP:
            character.moveUp(deltaTime);
            break;
        case Move::DOWN:
            character.moveDown(deltaTime);
            break;
        case Move::LEFT:
            character.moveLeft(deltaTime);
            break;
        case Move::RIGHT:
            character.moveRight(deltaTime);
            break;
        case Move::IDLE:
            character.stopMove(deltaTime);
            break;
    }
}