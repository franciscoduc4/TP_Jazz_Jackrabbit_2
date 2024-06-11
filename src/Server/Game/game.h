#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <map>
#include <memory>

#include "../../Common/DTO/game.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameInfo.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queueMonitor.h"
#include "../CommandHandlers/Game/gameCommand.h"
#include "../Threads/gameLoop.h"
#include "characters/character.h"

#include "gameMap.h"

class Game {
private:
    uint32_t gameId;
    std::string gameName;
    Episode episode;
    GameMode gameMode;
    uint8_t maxPlayers;
    uint8_t currentPlayers;
    GameLoopThread gameLoop;
    GameMap gameMap;

public:
    explicit Game(uint32_t gameId, std::string gameName, uint32_t playerId, Episode episode,
                  GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
                  std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                  QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor);


    uint32_t getGameId() const;

    std::string getGameName() const;

    void addPlayer(uint32_t playerId, CharacterType characterType);

    bool isFull() const;

    void removePlayer(uint32_t playerId);

    GameInfo getGameInfo();

    void launch();

    void endGame();
};

#endif  // GAME_H_
