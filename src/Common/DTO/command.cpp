#include "command.h"

CommandDTO::CommandDTO(): commandType(Command::IDLE), playerId(-1) {}

CommandDTO::CommandDTO(Command command): commandType(command), playerId(-1){}

CommandDTO::CommandDTO(const int32_t& playerId, Command command): playerId(playerId), commandType(command) {}

int32_t CommandDTO::getPlayerId() const { return playerId; }

Command CommandDTO::getCommand() const { return commandType; }

DTOType CommandDTO::getType() const { return type; }

std::vector<char> CommandDTO::getData() const {
    std::vector<char> data;
    return data;
}
