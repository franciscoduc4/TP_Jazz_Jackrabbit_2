#include "gamesList.h"

#include <unordered_map>
#include <utility>

GamesListDTO::GamesListDTO(): CommandDTO(Command::GAMES_LIST) {}

GamesListDTO::GamesListDTO(std::unordered_map<uint8_t, GameInfo> games):
        CommandDTO(Command::GAMES_LIST), games(std::move(games)) {}

std::unordered_map<uint8_t, GameInfo> GamesListDTO::getGames() const { return games; }

