#ifndef GAMES_LIST_DTO_H_
#define GAMES_LIST_DTO_H_

#include <unordered_map>
#include <string>

#include "../Types/gameInfo.h"

#include "command.h"

class GamesListDTO: public CommandDTO {
private:
    std::unordered_map<uint8_t, GameInfo> games;

public:
    GamesListDTO();
    GamesListDTO(std::unordered_map<uint8_t, GameInfo> games);

    std::unordered_map<uint8_t, GameInfo> getGames() const;

    ~GamesListDTO() {}
};


#endif  // GAMES_LIST_DTO_H_
