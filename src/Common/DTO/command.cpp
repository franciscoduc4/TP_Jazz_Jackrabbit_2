#include "command.h"

CommandDTO::CommandDTO(): commandType(Command::IDLE), playerId(-1) {}

CommandDTO::CommandDTO(Command command): commandType(command), playerId(-1) {}

CommandDTO::CommandDTO(int32_t& playerId, Command command):
        commandType(command), playerId(playerId) {}

Command CommandDTO::getCommand() const { return commandType; }

int CommandDTO::getPlayerId() const { return playerId; }

DTOType CommandDTO::getType() const { return type; }
