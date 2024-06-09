#include "deserializer.h"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "../Common/DTO/dto.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/queue.h"

Deserializer::Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Deserializer::deserialize_msg(std::unique_ptr<DTO>& dto) { queue->push(std::move(dto)); }

std::map<int32_t, std::vector<GameInfo>> Deserializer::getGamesList(std::unique_ptr<DTO>& dto) {
    std::map<int32_t, std::vector<GameInfo>> gamesList;
    auto* gamesListDTO = dynamic_cast<GamesListDTO*>(dto.get());
    for (auto& game : gamesListDTO->getGamesList()) {
        gamesList[game.getGameId()] = GameListInfo(game.getGameName(), game.getEpisode(), game.getMaxPlayers(),
                                                   game.getPlayers(), game.getGameMode());
    }
    return gamesList;
}