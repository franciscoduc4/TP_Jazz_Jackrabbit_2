#ifndef GAMES_LIST_DTO_H_
#define GAMES_LIST_DTO_H_

#include <map>
#include <string>

#include "../Types/gameInfo.h"

#include "command.h"

class GamesListDTO: public CommandDTO {
private:
    std::map<int32_t, GameInfo> games;

public:
    GamesListDTO();
    GamesListDTO(std::map<int32_t, GameInfo> games);

    std::map<int32_t, GameInfo> getGames() const;

    int32_t getMaxPlayers() const;

    int32_t getCurrentPlayers() const;
    ~GamesListDTO() {}
};


#endif  // GAMES_LIST_DTO_H_
