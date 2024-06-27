#include "cheat.h"

#include "DTO/cheat.h"

CheatHandler::CheatHandler(std::unique_ptr<CommandDTO> command) : command(std::move(command)) {}

void CheatHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    auto* cheatCommand = dynamic_cast<CheatDTO*>(command.get());
    switch (cheatCommand->getCheat()) {
        case Cheat::END_GAME: {
            keepRunning.store(false);
            break;
        }
        case Cheat::RESET_SCORES: {
            gameMap.resetScores();
            break;
        }
    }
}