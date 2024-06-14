#include "deserializer.h"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <iostream>

#include "../Common/DTO/dto.h"
#include "../Common/Types/gameMode.h"
#include "../Common/queue.h"

#include "../../Common/DTO/player.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/Types/entity.h"

Deserializer::Deserializer(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue,
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue) :
        lobbyQueue(lobbyQueue), gameQueue(gameQueue) {}

void Deserializer::deserialize_lobbyMsg(std::unique_ptr<DTO>& dto) {
    lobbyQueue->push(std::move(dto));
}

void Deserializer::deserialize_gameMsg(std::unique_ptr<DTO>& dto) {
    gameQueue->push(std::move(dto));
}

void Deserializer::setPlayerId(uint32_t playerId) {
    std::unique_ptr<DTO> player = std::make_unique<CommandDTO>(playerId, Command::IDLE);
    this->gameQueue->push(std::move(player));
}
