#ifndef SERVER_DESERIALIZER_H_
#define SERVER_DESERIALIZER_H_

#include <memory>
#include <string>
#include <vector>

#include "../../Common/DTO/characterType.h"
#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/move.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/DTO/switchWeapon.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

class Deserializer {
private:
    std::shared_ptr<Socket> socket;

    std::unique_ptr<CreateGameDTO> deserializeCreateGame(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<JoinGameDTO> deserializeJoinGame(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<CommandDTO> deserializeGamesList(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<CharacterTypeDTO> deserializeCharacterType(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<MoveDTO> deserializeMove(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<StartGameDTO> deserializeStart(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<CommandDTO> deserializeShooting(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<CommandDTO> deserializeSwitchWeapon(bool& wasClosed, int32_t& playerId);

    std::unique_ptr<CommandDTO> deserializeSprint(bool& wasClosed, int32_t& playerId);


public:
    explicit Deserializer(std::shared_ptr<Socket> socket);

    std::unique_ptr<CommandDTO> getCommand(bool& wasClosed, int32_t& playerId);
};
#endif  // SERVER_DESERIALIZER_H_
