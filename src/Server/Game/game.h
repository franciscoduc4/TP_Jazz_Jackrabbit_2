#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>

#include "../../Common/DTO/game.h"
#include "../../Common/Types/character.h"
#include "../Physics/playerCharacter.h"

class Game {
private:
    // Map gameMap;
    std::map<int32_t, std::shared_ptr<Character>> characters;


public:
    void addCharacter(int32_t playerId, CharacterType characterType);

    std::shared_ptr<Character> getCharacter(int32_t playerId);

    std::unique_ptr<GameDTO> getGameDTO();
};

#endif  // GAME_H_