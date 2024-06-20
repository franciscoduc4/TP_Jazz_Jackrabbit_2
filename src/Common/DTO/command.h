#ifndef COMMAND_DTO_H_
#define COMMAND_DTO_H_

#include <cstdint>
#include <vector>
#include <memory>

#include "../Types/command.h"

#include "dto.h"


class CommandDTO: public DTO {
private:
    Command commandType;

    uint8_t playerId;

    DTOType type = DTOType::COMMAND_DTO;


public:
    CommandDTO();

    explicit CommandDTO(Command command);

    CommandDTO(const uint8_t& playerId, Command command);

    uint8_t getPlayerId() const;

    Command getCommand() const;

    DTOType getType() const;

    virtual std::vector<char> getData() const;

    virtual std::unique_ptr<DTO> clone() const override;

    virtual ~CommandDTO() = default;
};
#endif  // COMMAND_DTO_H_
