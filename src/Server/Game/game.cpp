#include "game.h"

#include <utility>

Game::Game(Vector<int16_t> size): gameMap(size) {}

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


void Game::update(float time) { gameMap.update(time); }

bool Game::removeCharacter(int32_t playerId) {
    gameMap.removeCharacter({0, 0});
    return true;
}

std::unique_ptr<GameDTO> Game::getGameDTO() {
    return std::make_unique<GameDTO>(gameMap.getGameDTO());
}
