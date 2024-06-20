#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include <utility>
#include <memory>

#include "Types/gameInfo.h"
#include "command.h"
#include "dto.h"

class GameUpdateDTO : public CommandDTO {
private:
    GameInfo gameInfo;
public:
    explicit GameUpdateDTO(GameInfo gameInfo);
    GameInfo getGameInfo() const;
    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // GAMEUPDATE_H
