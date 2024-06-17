#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include <utility>

#include "Types/gameInfo.h"
#include "command.h"

class GameUpdateDTO : public CommandDTO {
private:
    GameInfo gameInfo;
public:
    explicit GameUpdateDTO(GameInfo gameInfo);
    GameInfo getGameInfo() const;

};

#endif  // GAMEUPDATE_H
