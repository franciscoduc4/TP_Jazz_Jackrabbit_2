#include "gamesList.h"
#include <utility>
#include <map>

GamesListDTO::GamesListDTO(std::map<int32_t, GameInfo> games): 
    games(std::move(games)) {}

std::map<int32_t, GameInfo> GamesListDTO::getGames() const { return games; }

