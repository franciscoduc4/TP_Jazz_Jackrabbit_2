#include "gameUpdate.h"

GameUpdateDTO::GameUpdateDTO(GameInfo gameInfo) :
        CommandDTO(Command::GAME_UPDATE), gameInfo(std::move(gameInfo)) {}

GameInfo GameUpdateDTO::getGameInfo() const {
    return this->gameInfo;
}
