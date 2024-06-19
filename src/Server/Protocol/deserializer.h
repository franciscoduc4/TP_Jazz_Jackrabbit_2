#ifndef SERVER_DESERIALIZER_H_
#define SERVER_DESERIALIZER_H_

#include <memory>
#include <string>
#include <vector>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/gameCommand.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/DTO/switchWeapon.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

class Deserializer {
private:
    std::shared_ptr<Socket> socket;

    std::unique_ptr<CreateGameDTO> deserializeCreateGame(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<MapsListDTO> deserializeMapsList(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<JoinGameDTO> deserializeJoinGame(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<CommandDTO> deserializeGamesList(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<GameCommandDTO> deserializeMove(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<CommandDTO> deserializeIdle(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<StartGameDTO> deserializeStart(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<CommandDTO> deserializeShooting(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<CommandDTO> deserializeSwitchWeapon(bool& wasClosed, uint8_t& playerId);

    std::unique_ptr<CommandDTO> deserializeSprint(bool& wasClosed, uint8_t& playerId);


public:
    explicit Deserializer(std::shared_ptr<Socket> socket);

    std::unique_ptr<CommandDTO> getCommand(bool& wasClosed, uint8_t& playerId);
};
#endif  // SERVER_DESERIALIZER_H_
