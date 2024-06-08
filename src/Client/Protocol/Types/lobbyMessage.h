#ifndef LOBBY_MESSAGE_H
#define LOBBY_MESSAGE_H

#include <sstream>
#include <string>
#include <utility>

#include "../../../Common/Types/character.h"
#include "../../../Common/Types/episode.h"
#include "../../../Common/Types/command.h"

struct LobbyMessage {
    std::string playerName;
    Command cmd;
    int8_t maxPlayers;
    std::string gameName;
    int32_t gameId;
    CharacterType character;
    Episode episode;

    LobbyMessage():
            playerName(""),
            cmd(Command::IDLE),
            maxPlayers(0),
            gameName(""),
            gameId(-1),
            character(CharacterType::INVALID),
            episode(Episode::INVALID) {}

    LobbyMessage(std::string  playerName,
                 const Command& cmd,
                 const int8_t& maxPlayers, std::string  gameName, const int32_t& gameId,
                 const CharacterType& character, const Episode& episode):
            playerName(std::move(playerName)),
            cmd(cmd),
            maxPlayers(maxPlayers),
            gameName(std::move(gameName)),
            gameId(gameId),
            character(character),
            episode(episode) {}

    void setPlayerName(const std::string& name) { playerName = name; }

    void setLobbyCmd(const Command& command) {
        cmd = command;
    }

    void setMaxPlayers(const int8_t& players) { maxPlayers = players; }

    void setGameName(const std::string& name) { gameName = name; }

    void setGameId(const int32_t& id) { gameId = id; }

    void setCharacter(CharacterType selectedCharacter) { character = selectedCharacter; }

    void setEpisode(Episode ep) { episode = ep; }

    std::string getPlayerName() const { return playerName; }

    Command getLobbyCmd() const { return cmd; }

    int8_t getMaxPlayers() const { return maxPlayers; }

    std::string getGameName() const { return gameName; }

    int32_t getGameId() const { return gameId; }

    CharacterType getCharacter() const { return character; }

    Episode getEpisode() const { return episode; }

    LobbyMessage& build(const std::string& namePlayer,
                        Command lobbyCmd,
                        int8_t maxPlayerNumber, const std::string& nameGame, int32_t idGame,
                        CharacterType characterType, Episode ep) {
        this->playerName = namePlayer;
        this->cmd = lobbyCmd;
        this->maxPlayers = maxPlayerNumber;
        this->gameName = nameGame;
        this->gameId = idGame;
        this->character = characterType;
        this->episode = ep;
        return *this;
    }
};

#endif  // LOBBY_MESSAGE_H
