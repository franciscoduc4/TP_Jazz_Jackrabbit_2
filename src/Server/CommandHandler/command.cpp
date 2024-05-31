#include "command.h"

#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/startGame.h"

#include "createGame.h"
#include "joinGame.h"
#include "startGame.h"

std::unique_ptr<CommandHandler> CommandHandler::createHandler(std::unique_ptr<CommandDTO> command) {
    switch (command->getCommand()) {
        case Command::CREATE_GAME: {
            auto createGameCommand = dynamic_cast<CreateGameDTO*>(command.get());
            command.release();
            return std::make_unique<CreateGameHandler>(
                    std::unique_ptr<CreateGameDTO>(createGameCommand));
            }
        case Command::JOIN_GAME:{
            auto joinGameCommand = dynamic_cast<JoinGameDTO*>(command.get());
            command.release();
            return std::make_unique<JoinGameHandler>(std::unique_ptr<JoinGameDTO>(joinGameCommand));
        }
        case Command::START_GAME:{
            auto startGameCommand = dynamic_cast<StartGameDTO*>(command.get());
            command.release();
            return std::make_unique<StartGameHandler>(
                    std::unique_ptr<StartGameDTO>(startGameCommand));
        }
        default:
            return nullptr;
    }
}
