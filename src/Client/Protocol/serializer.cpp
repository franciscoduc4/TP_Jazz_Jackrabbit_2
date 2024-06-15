#include "serializer.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "../../Common/DTO/dto.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/direction.h"
#include "../../Common/maps/mapsManager.h"
#include "../../Common/queue.h"
#include "DTO/command.h"
#include "DTO/createGame.h"
#include "DTO/joinGame.h"
#include "DTO/startGame.h"

Serializer::Serializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue): queue(queue) {}

void Serializer::sendMsg(std::unique_ptr<DTO>& dto) { this->queue->push(std::move(dto)); }

void Serializer::serializeLobbyMessage(const LobbyMessage& msg) {
    try {
        switch (msg.getLobbyCmd()) {
            case Command::GAMES_LIST:
                this->queue->push(std::make_unique<GamesListDTO>());
                break;
            case Command::JOIN_GAME:
                this->queue->push(
                        std::make_unique<JoinGameDTO>(msg.getGameId(), msg.getCharacter()));
                break;
            case Command::CREATE_GAME: {
                uint8_t mapId = htonl(msg.getMap());
                this->queue->push(std::make_unique<CreateGameDTO>(
                        mapId, msg.getMaxPlayers(), msg.getCharacter(), msg.getGameName()));
                break;
            }
            case Command::START_GAME: {
                this->queue->push(std::make_unique<StartGameDTO>(msg.getGameId()));
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
