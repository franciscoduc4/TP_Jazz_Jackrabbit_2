#include "gamesList.h"
#include <utility>
#include <map>

GamesListDTO::GamesListDTO(std::map<int32_t, GameInfo> games): 
    CommandDTO(Command::GAMES_LIST), games(std::move(games)) {}

std::map<int32_t, GameInfo> GamesListDTO::getGames() const { return games; }

