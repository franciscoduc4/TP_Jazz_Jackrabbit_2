#ifndef COMMAND_DTO_H_
#define COMMAND_DTO_H_

#include <cstdint>
#include <vector>

#include "../Types/command.h"

#include "dto.h"


class CommandDTO: public DTO {
private:
    Command commandType;

    uint32_t playerId;

    DTOType type = DTOType::COMMAND_DTO;


public:
    CommandDTO();

    explicit CommandDTO(Command command);

    CommandDTO(const uint32_t& playerId, Command command);

    uint32_t getPlayerId() const;

    Command getCommand() const;

    DTOType getType() const;

    virtual std::vector<char> getData() const;

    virtual ~CommandDTO() = default;
};
#endif  // COMMAND_DTO_H_
