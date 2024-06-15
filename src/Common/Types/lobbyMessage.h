#ifndef LOBBY_MESSAGE_H
#define LOBBY_MESSAGE_H

#include <sstream>
#include <string>
#include <utility>

#include "Types/character.h"
#include "Types/command.h"

struct LobbyMessage {
    std::string playerName;
    Command cmd;
    int8_t maxPlayers;
    std::string gameName;
    uint8_t gameId;
    CharacterType character;
    uint8_t mapId;

    LobbyMessage():
            playerName(""),
            cmd(Command::IDLE),
            maxPlayers(0),
            gameName(""),
            gameId(-1),
            character(CharacterType::INVALID),
            mapId(-1) {}

    LobbyMessage(std::string playerName, const Command& cmd, const int8_t& maxPlayers,
                 std::string gameName, const uint8_t& gameId, const CharacterType& character,
                 const uint8_t& mapId):
            playerName(std::move(playerName)),
            cmd(cmd),
            maxPlayers(maxPlayers),
            gameName(std::move(gameName)),
            gameId(gameId),
            character(character),
            mapId(mapId) {}

    void setPlayerName(const std::string& name) { playerName = name; }

    void setLobbyCmd(const Command& command) { cmd = command; }

    void setMaxPlayers(const int8_t& players) { maxPlayers = players; }

    void setGameName(const std::string& name) { gameName = name; }

    void setGameId(const uint8_t& id) { gameId = id; }

    void setCharacter(CharacterType selectedCharacter) { character = selectedCharacter; }

    void setMap(const uint8_t& id) { mapId = id; }

    std::string getPlayerName() const { return playerName; }

    Command getLobbyCmd() const { return cmd; }

    int8_t getMaxPlayers() const { return maxPlayers; }

    std::string getGameName() const { return gameName; }

    uint8_t getGameId() const { return gameId; }

    CharacterType getCharacter() const { return character; }

    uint8_t getMap() const { return mapId; }

    LobbyMessage& build(const std::string& namePlayer, Command lobbyCmd, int8_t maxPlayerNumber,
                        const std::string& nameGame, uint8_t idGame, CharacterType characterType,
                        const uint8_t& idMap) {
        this->playerName = namePlayer;
        this->cmd = lobbyCmd;
        this->maxPlayers = maxPlayerNumber;
        this->gameName = nameGame;
        this->gameId = idGame;
        this->character = characterType;
        this->mapId = idMap;
        return *this;
    }
};

#endif  // LOBBY_MESSAGE_H
