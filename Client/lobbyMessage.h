#ifndef LOBBY_MESSAGE_H
#define LOBBY_MESSAGE_H

#include <string>
#include "../Common/Constants/lobbyCommands.h"
#include "../Common/Constants/characterSelect.h"
#include "../Common/Constants/episodeSelect.h"

struct LobbyMessage {
    std::string playerName;
    LobbyCommands lobbyCmd;
    int maxPlayers;
    std::string gameName;
    int waitTime;
    CharacterSelect character;
    EpisodeSelect episode;

    LobbyMessage() : 
        playerName(""), 
        lobbyCmd(LobbyCommands::INVALID_CMD),
        maxPlayers(0),
        gameName(""),
        waitTime(0),
        character(CharacterSelect::INVALID),
        episode(EpisodeSelect::INVALID) {}

    void setPlayerName(const std::string& name) {
        playerName = name;
    }

    void setLobbyCmd(LobbyCommands cmd) {
        lobbyCmd = cmd;
    }

    void setMaxPlayers(int players) {
        maxPlayers = players;
    }

    void setGameName(const std::string& name) {
        gameName = name;
    }

    void setWaitTime(int time) {
        waitTime = time;
    }

    void setCharacter(CharacterSelect chara) {
        character = chara;
    }

    void setEpisode(EpisodeSelect ep) {
        episode = ep;
    }

    bool isCreateGame() {
        return lobbyCmd == LobbyCommands::CREATE_GAME;
    }

    bool isJoinGame() {
        return lobbyCmd == LobbyCommands::JOIN_GAME;
    }
};

#endif // CLIENT_LOBBYMESSAGE_H
