#include "serializer.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "../../Common/DTO/dto.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/maps/mapsManager.h"
#include "../../Common/queue.h"
#include "DTO/command.h"
#include "DTO/createGame.h"
#include "DTO/joinGame.h"
#include "DTO/startGame.h"

Serializer::Serializer(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue): queue(queue) {}

void Serializer::sendMsg(std::unique_ptr<CommandDTO>& dto) { this->queue->push(std::move(dto)); }

void Serializer::serializeLobbyMessage(const LobbyMessage& msg) {
    try {
        switch (msg.getLobbyCmd()) {
            case Command::CREATE_GAME:
                std::cout << "[CLIENT SERIALIZER] Pushing CreateGameDTO to queue." << std::endl;
                this->queue->push(std::make_unique<CreateGameDTO>(
                        msg.getMap(), msg.getMaxPlayers(), msg.getCharacter(), msg.getGameName()));
                break;
            case Command::JOIN_GAME:
                std::cout << "[CLIENT SERIALIZER] Pushing JoinGameDTO to queue." << std::endl;
                this->queue->push(
                        std::make_unique<JoinGameDTO>(msg.getGameId(), msg.getCharacter()));
                break;
            case Command::GAMES_LIST:
                std::cout << "[CLIENT SERIALIZER] Pushing GamesListDTO to queue." << std::endl;
                this->queue->push(std::make_unique<GamesListDTO>());
            case Command::MAPS_LIST:
                std::cout << "[CLIENT SERIALIZER] Pushing MapsListDTO to queue." << std::endl;
                this->queue->push(std::make_unique<MapsListDTO>());
                break;
            case Command::START_GAME:
                std::cout << "[CLIENT SERIALIZER] Pushing StartGameDTO to queue." << std::endl;
                this->queue->push(std::make_unique<StartGameDTO>(msg.getGameId()));
                break;
            default:
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in serializeLobbyMessage: " << e.what() << std::endl;
        throw;
    }
}
