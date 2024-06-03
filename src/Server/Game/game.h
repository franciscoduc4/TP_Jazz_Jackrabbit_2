#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>
#include <memory>

#include "../../Common/DTO/game.h"
#include "../../Common/Types/character.h"
#include "../CommandHandlers/Game/gameCommand.h"
#include "../Physics/gameMap.h"
#include "../Physics/playerCharacter.h"

class Game {
private:
    GameMap gameMap;
    std::map<int32_t, std::shared_ptr<Character>> characters;


public:
    explicit Game(Vector<int16_t> size);
    void handleCommand(std::unique_ptr<CommandDTO> commandDTO, std::atomic<bool>& keepRunning,
                       double deltaTime);

    void addCharacter(int32_t playerId, CharacterType characterType);

    std::shared_ptr<Character> getCharacter(int32_t playerId);

    std::unique_ptr<GameDTO> getGameDTO();

    void update(float time);
};

#endif  // GAME_H_
