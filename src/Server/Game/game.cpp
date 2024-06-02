#include "game.h"

void Game::handleCommand(std::unique_ptr<CommandDTO> commandDTO, std::atomic<bool>& keepRunning,
                         double deltaTime) {
    std::unique_ptr<GameCommandHandler> handler =
            GameCommandHandler::createHandler(std::move(commandDTO));
    handler->execute(*this, keepRunning, deltaTime);
}

void Game::addCharacter(int32_t playerId, CharacterType characterType) {
    characters[playerId] = gameMap.addCharacter(characterType);
}

std::shared_ptr<Character> Game::getCharacter(int32_t playerId) { return characters[playerId]; }

std::unique_ptr<GameDTO> Game::getGameDTO() {}