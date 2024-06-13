#include "serializer.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include <arpa/inet.h>
#include "../../Common/DTO/dto.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/queue.h"
#include "../../Common/maps/mapsManager.h"
#include "DTO/command.h"
#include "DTO/createGame.h"
#include "DTO/joinGame.h"

Serializer::Serializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Serializer::sendMsg(std::unique_ptr<DTO>& dto) {
    this->queue->push(std::move(dto));
}

void Serializer::serializeLobbyMessage(const LobbyMessage& msg) {
    try {
        switch (msg.getLobbyCmd()) {
            case Command::GAMES_LIST:
                this->queue->push(std::make_unique<CommandDTO>(Command::GAMES_LIST));
                break;
            case Command::JOIN_GAME:
                this->queue->push(std::make_unique<JoinGameDTO>(msg.getGameId(), msg.getCharacter()));
                break;
            case Command::CREATE_GAME: {
                std::cout << "mapId" << msg.getMap() << std::endl;
                uint32_t mapId = htonl(msg.getMap());
                std::cout << "mapId post ton" << mapId << std::endl;

                std::cout << "Creating game" << std::endl;
                this->queue->push(std::make_unique<CreateGameDTO>(mapId, msg.getMaxPlayers(),
                                                                  msg.getCharacter(), msg.getGameName()));
                std::cout << "Game pushed" << std::endl;
                break;
            }
            default:
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in serializeLobbyMessage: " << e.what() << std::endl;
        throw;
    }
}
