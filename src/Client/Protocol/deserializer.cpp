#include "deserializer.h"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "../Common/DTO/dto.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/queue.h"

Deserializer::Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue) :
        lobbyQueue(lobbyQueue), gameQueue(gameQueue) {}

void Deserializer::deserialize_lobbyMsg(std::unique_ptr<DTO>& dto) {
    lobbyQueue->push(std::move(dto));
}

void Deserializer::deserialize_gameMsg(std::unique_ptr<DTO>& dto) {
    gameQueue->push(std::move(dto));
}

/*
std::map<int32_t, std::vector<GameInfo>> Deserializer::getGamesList(std::unique_ptr<DTO>& dto) {
    std::map<int32_t, std::vector<GameInfo>> gamesList;
    auto* gamesListDTO = dynamic_cast<GamesListDTO*>(dto.get());
    for (auto& game : gamesListDTO->getGamesList()) {
        gamesList[game.getGameId()] = GameListInfo(game.getGameName(), game.getEpisode(), game.getMaxPlayers(),
                                                   game.getPlayers(), game.getGameMode());
    }
    return gamesList;
}
*/