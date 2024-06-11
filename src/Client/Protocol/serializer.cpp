#include "serializer.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>
#include "../../Common/DTO/dto.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/queue.h"
#include "DTO/command.h"
#include "DTO/createGame.h"
#include "DTO/joinGame.h"


Serializer::Serializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Serializer::sendMsg(std::unique_ptr<DTO>& dto) { this->queue->push(std::move(dto)); }

void Serializer::serializeLobbyMessage(const LobbyMessage& msg) {
    switch(msg.getLobbyCmd()) {
        case Command::GAMES_LIST:
            this->queue->push(std::make_unique<CommandDTO>(Command::GAMES_LIST));
            break;
        case Command::JOIN_GAME:
            this->queue->push(std::make_unique<JoinGameDTO>(msg.getGameId(), msg.getCharacter()));
            break;
        case Command::CREATE_GAME:
            std::cout << "Creating game" << std::endl;
            this->queue->push(std::make_unique<CreateGameDTO>(msg.getEpisode(), msg.getMaxPlayers(),
                                                              msg.getCharacter(), msg.getGameName(), msg.getGameId()));
            break;
        default:
            break;
    }
}