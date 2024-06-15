#include "GameController.h"
#include "../Common/Types/direction.h"
#include "../Common/DTO/gameCommand.h"


GameController::GameController(Serializer& serializer, Deserializer& deserializer,
                               std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue):
        serializer(serializer), deserializer(deserializer), gameQueue(gameQueue) {}

void GameController::sendMsg(uint8_t playerId, Command& cmd, std::vector<uint8_t>& parameters) {
    switch (cmd) {
        case Command::IDLE:
            idle_msg(playerId);
        case Command::MOVE:
            move_msg(playerId, parameters);
            break;
        case Command::SHOOT:
            shoot_msg(playerId);
            break;
    }
}

void GameController::move_msg(uint8_t playerId, std::vector<uint8_t>& parameters) {
    Direction dir = static_cast<Direction>(parameters[0]);
    std::unique_ptr<CommandDTO> move =
		std::make_unique<GameCommandDTO>(playerId, dir, Command::MOVE);
    this->serializer.sendMsg(move);
}

void GameController::shoot_msg(uint8_t playerId) {
	std::unique_ptr<CommandDTO> shoot = std::make_unique<CommandDTO>(playerId, Command::SHOOT);
	this->serializer.sendMsg(shoot);
}

void GameController::idle_msg(uint8_t playerId) {
    std::unique_ptr<CommandDTO> idle = std::make_unique<GameCommandDTO>(playerId, Direction::RIGHT, Command::IDLE);
	this->serializer.sendMsg(idle);
}


std::unique_ptr<DTO> GameController::getServerMsg() {
    std::unique_ptr<DTO> dto;
    this->gameQueue->try_pop(dto);
    return dto;
}
