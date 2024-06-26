#include "lobbyCommand.h"

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/joinGame.h"
#include "../../../Common/DTO/mapsList.h"
#include "../../../Common/DTO/startGame.h"

#include "createGame.h"
#include "gamesList.h"
#include "joinGame.h"
#include "mapsListHandler.h"
#include "startGame.h"

std::unique_ptr<LobbyCommandHandler> LobbyCommandHandler::createHandler(
        std::unique_ptr<CommandDTO> command, uint8_t gameId) {
    switch (command->getCommand()) {
        case Command::CREATE_GAME: {
            auto createGameCommand = dynamic_cast<CreateGameDTO*>(command.get());
            command.release();
            return std::make_unique<CreateGameHandler>(
                    std::unique_ptr<CreateGameDTO>(createGameCommand));
        }
        case Command::MAPS_LIST: {
            auto mapsListCommand = dynamic_cast<MapsListDTO*>(command.get());
            command.release();
            return std::make_unique<MapsListHandler>(
                    std::unique_ptr<MapsListDTO>(mapsListCommand));
        }
        case Command::JOIN_GAME: {
            auto joinGameCommand = dynamic_cast<JoinGameDTO*>(command.get());
            command.release();
            return std::make_unique<JoinGameHandler>(std::unique_ptr<JoinGameDTO>(joinGameCommand));
        }
        case Command::START_GAME: {
            auto startGameCommand = dynamic_cast<StartGameDTO*>(command.get());
            startGameCommand->setGameId(gameId);
            command.release();
            return std::make_unique<StartGameHandler>(
                    std::unique_ptr<StartGameDTO>(startGameCommand));
        }
        case Command::GAMES_LIST: {
            return std::make_unique<GamesListHandler>(
                    std::unique_ptr<CommandDTO>(command.release()));
        }
        default:
            return nullptr;
    }
}
