#include "gamesList.h"

#include <map>
#include <utility>

GamesListDTO::GamesListDTO(): CommandDTO(Command::GAMES_LIST) {}

GamesListDTO::GamesListDTO(std::unordered_map<uint32_t, GameInfo> games):
        CommandDTO(Command::GAMES_LIST), games(std::move(games)) {}

std::unordered_map<uint32_t, GameInfo> GamesListDTO::getGames() const { return games; }

