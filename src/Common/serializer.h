#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <sstream>
#include <string>

#include "../Client/Protocol/lobbyMessage.h"

class Serializer {
  public:
    static ProtocolMessage parseSendMessage(const std::string& protocolMessage) {
        uint8_t messageSize = protocolMessage.size();
        return ProtocolMessage(messageSize, protocolMessage);
    }

    static LobbyMessage parseRecvMessage(const ProtocolMessage& message){
      std::stringstream is(message.args);
      std::string playerName;
      int lobbyCmdInt;
      int maxPlayers;
      std::string gameName;
      int waitTime;
      int characterInt;
      int mapInt;
      int playerID;

      is >> playerName;
      is >> lobbyCmdInt;
      is >> maxPlayers;
      is >> gameName;
      is >> waitTime;
      is >> characterInt;
      is >> mapInt;
      is >> playerID;

      LobbyCommands lobbyCmd = static_cast<LobbyCommands>(lobbyCmdInt);
      CharacterSelect character = static_cast<CharacterSelect>(characterInt);
      EpisodeSelect episode = static_cast<EpisodeSelect>(mapInt);

      return LobbyMessage(playerName,
                          lobbyCmd,
                          maxPlayers,
                          gameName,
                          waitTime,
                          character,
                          episode,
                          playerID);
    }
      
};

#endif  // SERIALIZER_H_
