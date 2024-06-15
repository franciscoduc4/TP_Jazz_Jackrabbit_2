#ifndef GAMES_LIST_DTO_H_
#define GAMES_LIST_DTO_H_

#include <map>
#include <string>

#include "../Types/gameInfo.h"

#include "command.h"

class GamesListDTO: public CommandDTO {
private:
    std::map<uint8_t, GameInfo> games;

public:
    GamesListDTO();
    GamesListDTO(std::map<uint8_t, GameInfo> games);

    std::map<uint8_t, GameInfo> getGames() const;

    uint8_t getMaxPlayers() const;

    uint8_t getCurrentPlayers() const;
    ~GamesListDTO() {}
};


#endif  // GAMES_LIST_DTO_H_
