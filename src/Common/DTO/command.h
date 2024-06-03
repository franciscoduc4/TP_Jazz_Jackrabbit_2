#ifndef COMMAND_DTO_H_
#define COMMAND_DTO_H_

#include <cstdint>
#include <vector>

#include "../Types/command.h"

#include "dto.h"


class CommandDTO: public DTO {
private:
    Command commandType;

    int32_t playerId;

    DTOType type = DTOType::COMMAND_DTO;


public:
    CommandDTO();

    explicit CommandDTO(Command command);

    CommandDTO(int32_t& playerId, Command command);

    Command getCommand() const;

    int getPlayerId() const;

    DTOType getType() const;

    virtual ~CommandDTO() {}
};
#endif  // COMMAND_DTO_H_
