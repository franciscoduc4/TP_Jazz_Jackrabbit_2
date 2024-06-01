#include "game.h"

void Game::addCharacter(int32_t playerId, CharacterType characterType) {
    // characters[playerId] = Character(playerId, characterType, etc..)
}

std::shared_ptr<Character> Game::getCharacter(int32_t playerId) { return characters[playerId]; }

std::unique_ptr<GameDTO> Game::getGameDTO() {}