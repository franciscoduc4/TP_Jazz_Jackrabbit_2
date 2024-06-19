#include "joinGame.h"

JoinGameDTO::JoinGameDTO(const uint8_t& gameId, CharacterType characterType):
        CommandDTO(-1, Command::JOIN_GAME),
        gameId(gameId),
        characterType(characterType),
        currentPlayers(0),
        joined(false) {}

JoinGameDTO::JoinGameDTO(const uint8_t& gameId, const uint8_t& currentPlayers):
        CommandDTO(-1, Command::JOIN_GAME),
        gameId(gameId),
        characterType(CharacterType::INVALID),
        currentPlayers(currentPlayers),
        joined(false) {}

JoinGameDTO::JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId,
                         CharacterType characterType):
        CommandDTO(playerId, Command::JOIN_GAME),
        gameId(gameId),
        characterType(characterType),
        currentPlayers(0),
        joined(false) {}

JoinGameDTO::JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId,
                         const uint8_t& currentPlayers):
        CommandDTO(playerId, Command::JOIN_GAME),
        gameId(gameId),
        characterType(CharacterType::INVALID),
        currentPlayers(currentPlayers),
        joined(false) {}

JoinGameDTO::JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId,
                         const uint8_t& currentPlayers, CharacterType characterType):
        CommandDTO(playerId, Command::JOIN_GAME),
        gameId(gameId),
        characterType(characterType),
        currentPlayers(currentPlayers),
        joined(false) {}

JoinGameDTO::JoinGameDTO(bool status):
        CommandDTO(-1, Command::JOIN_GAME),
        gameId(-1),
        characterType(CharacterType::INVALID),
        currentPlayers(0),
        joined(status) {}


uint8_t JoinGameDTO::getGameId() const { return gameId; }

CharacterType JoinGameDTO::getCharacterType() const { return characterType; }

bool JoinGameDTO::getJoined() const { return joined; }

uint8_t JoinGameDTO::getCurrentPlayers() const { return currentPlayers; }

std::vector<char> JoinGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(gameId));
    data.push_back(static_cast<char>(characterType));
    return data;
}

std::unique_ptr<DTO> JoinGameDTO::clone() const {
    return std::make_unique<JoinGameDTO>(*this);
}