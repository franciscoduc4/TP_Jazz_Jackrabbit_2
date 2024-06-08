#include "joinGame.h"

JoinGameDTO::JoinGameDTO(const int32_t& gameId, CharacterType characterType):
        CommandDTO(-1, Command::JOIN_GAME), gameId(gameId), characterType(characterType), joined(false) {}

JoinGameDTO::JoinGameDTO(const int32_t& playerId, const int32_t& gameId, CharacterType characterType):
        CommandDTO(playerId, Command::JOIN_GAME), gameId(gameId), characterType(characterType), joined(false) {}

JoinGameDTO::JoinGameDTO(bool status): CommandDTO(-1, Command::JOIN_GAME), gameId(-1), characterType(CharacterType::INVALID), joined(status) {}

int32_t JoinGameDTO::getGameId() const { return gameId; }

CharacterType JoinGameDTO::getCharacterType() const { return characterType; }

bool JoinGameDTO::getJoined() const { return joined; }

std::vector<char> JoinGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(gameId));
    data.push_back(static_cast<char>(characterType));
    return data;
}