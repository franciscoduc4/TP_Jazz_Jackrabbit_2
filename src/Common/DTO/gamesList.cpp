#include "gamesList.h"
#include <utility>
#include <map>

GamesListDTO::GamesListDTO(std::map<int32_t, std::string> games): games(std::move(games)) {}

std::map<int32_t, std::string> GamesListDTO::getGames() const { return games; }
