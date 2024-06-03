#include "jump.h"

JumpHandler::JumpHandler(std::unique_ptr<CommandDTO> jumpCommand):
        moveCommand(std::move(jumpCommand)) {}

void JumpHandler::execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = game.getCharacter(moveCommand->getPlayerId());
    // character->jump(deltaTime);
}