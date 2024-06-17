#include "gameUpdate.h"

GameUpdate::GameUpdate(GameInfo gameInfo) :
        CommandDTO(Command::GAME_UPDATE), gameInfo(std::move(gameInfo)) {}

GameInfo GameUpdate::getGameInfo() const {
    return this->gameInfo;
}