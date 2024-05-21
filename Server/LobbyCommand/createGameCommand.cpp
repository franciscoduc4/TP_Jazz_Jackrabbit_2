#include "createGameCommand.h"

#include <memory>
#include <string>

#include "../../Common/Models/character.h"

CreateGameCommand::CreateGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage CreateGameCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol,
                                        bool& inLobby) {
    std::stringstream argsIt(args);

    int maxPlayers;
    std::string gameName;
    std::string character;

    argsIt >> maxPlayers;
    argsIt >> gameName;
    argsIt >> character;

    Player player(std::move(protocol));
    std::unique_ptr<Character> playerCharacter = Character::createCharacter(character);
    gameMonitor.createGame(gameName, maxPlayers, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
