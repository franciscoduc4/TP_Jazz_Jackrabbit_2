#ifndef SERVER_DESERIALIZER_H_
#define SERVER_DESERIALIZER_H_

#include <memory>
#include <string>
#include <vector>
#include <atomic>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/gameCommand.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/DTO/switchWeapon.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

class Deserializer {
private:
    std::shared_ptr<Socket> socket;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    bool wasClosed;

    // Receive Types
    bool receive_uint8(uint8_t& value);
    bool receive_char(char& value);
    bool receive_vector_char(std::vector<char>& buffer);
    // Lobby
    std::unique_ptr<CreateGameDTO> deserializeCreateGame(uint8_t& playerId);
    static std::unique_ptr<MapsListDTO> deserializeMapsList(uint8_t& playerId);
    std::unique_ptr<JoinGameDTO> deserializeJoinGame(uint8_t& playerId);
    static std::unique_ptr<CommandDTO> deserializeGamesList(uint8_t& playerId);

    // Game
    std::unique_ptr<CommandDTO> deserializeIdle(uint8_t& playerId);
    std::unique_ptr<GameCommandDTO> deserializeMove(uint8_t& playerId);
    std::unique_ptr<StartGameDTO> deserializeStart(uint8_t& playerId);
    std::unique_ptr<CommandDTO> deserializeShooting(uint8_t& playerId);
    std::unique_ptr<CommandDTO> deserializeSwitchWeapon(uint8_t& playerId);
    std::unique_ptr<CommandDTO> deserializeSprint(uint8_t& playerId);
    std::unique_ptr<CommandDTO> deserializeJumping(uint8_t& playerId);


public:
    Deserializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame);

    std::unique_ptr<CommandDTO> getCommand(uint8_t& playerId);
};
#endif  // SERVER_DESERIALIZER_H_
