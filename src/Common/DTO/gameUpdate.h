#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include "Types/gameInfo.h"

#include "command.h"

class GameUpdate : public CommandDTO {
private:
    GameInfo gameInfo;
public:
    GameUpdate(GameInfo gameInfo);
    GameInfo getGameInfo() const;

};

#endif  // GAMEUPDATE_H
