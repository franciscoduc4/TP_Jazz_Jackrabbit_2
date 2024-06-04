#ifndef LOBBY_MESSAGE_H
#define LOBBY_MESSAGE_H

#include <sstream>
#include <string>

#include "../../../Common/Types/character.h"
#include "../../../Common/Types/episode.h"
// #include "../../../Common/Types/lobbyCommands.h"

struct LobbyMessage {
    std::string playerName;
    // LobbyCommands lobbyCmd;
    int maxPlayers;
    std::string gameName;
    int waitTime;
    CharacterType character;
    Episode episode;
    int playerId;

    LobbyMessage():
            playerName(""),
            // lobbyCmd(LobbyCommands::INVALID_CMD),
            maxPlayers(0),
            gameName(""),
            waitTime(0),
            character(CharacterType::INVALID),
            episode(Episode::INVALID),
            playerId(-1) {}

    LobbyMessage(const std::string& playerName,
                 // const LobbyCommands& lobbyCmd,
                 const int& maxPlayers, const std::string& gameName, const int& waitTime,
                 const CharacterType& character, const Episode& episode, const int& playerId):
            playerName(playerName),
            // lobbyCmd(lobbyCmd),
            maxPlayers(maxPlayers),
            gameName(gameName),
            waitTime(waitTime),
            character(character),
            episode(episode),
            playerId(playerId) {}

    void setPlayerName(const std::string& name) { playerName = name; }

    std::string getPlayerName() { return playerName; }

    /*
    void setLobbyCmd(LobbyCommands cmd) {
        lobbyCmd = cmd;
    }
    */

    void setMaxPlayers(int players) { maxPlayers = players; }

    void setGameName(const std::string& name) { gameName = name; }

    void setWaitTime(int time) { waitTime = time; }

    void setCharacter(CharacterType selectedCharacter) { character = selectedCharacter; }

    void setEpisode(Episode ep) { episode = ep; }

    /*
    bool isCreateGame() {
        return lobbyCmd == LobbyCommands::CREATE_GAME;
    }

    bool isJoinGame() {
        return lobbyCmd == LobbyCommands::JOIN_GAME;
    }
    */

    std::string toString() {
        std::stringstream ss;
        ss << playerName
           // << static_cast<int>(lobbyCmd)
           << maxPlayers << gameName << waitTime << static_cast<int>(character)
           << static_cast<int>(episode);
        return ss.str();
    }

    LobbyMessage& build(const std::string& playerName,
                        // LobbyCommands lobbyCmd,
                        int maxPlayers, const std::string& gameName, int waitTime,
                        CharacterType character, Episode episode, int playerId) {
        this->playerName = playerName;
        // this->lobbyCmd = lobbyCmd;
        this->maxPlayers = maxPlayers;
        this->gameName = gameName;
        this->waitTime = waitTime;
        this->character = character;
        this->episode = episode;
        this->playerId = playerId;
        return *this;
    }
};

#endif  // CLIENT_LOBBYMESSAGE_H
