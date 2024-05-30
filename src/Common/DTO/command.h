#ifndef COMMAND_DTO_H_
#define COMMAND_DTO_H_

#include <cstdint>
#include <vector>

#include "../Types/command.h"


class CommandDTO {
private:
    Command commandType;

    int32_t playerId;

public:
    CommandDTO();

    explicit CommandDTO(Command command);

    CommandDTO(int32_t& playerId, Command command);

    Command getCommand() const;

    int getPlayerId() const;

    virtual ~CommandDTO() {}
};
#endif  // COMMAND_DTO_H_
