#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/lobby.h"
#include "../../Common/DTO/move.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

class Serializer {
private:
    std::shared_ptr<Socket> socket;

public:
    std::vector<char> serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto);
    std::vector<char> serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto);
    std::vector<char> serializeGamesList(const std::unique_ptr<CommandDTO>& dto);
    std::vector<char> serializeMove(const std::unique_ptr<MoveDTO>& dto);
    std::vector<char> serializeStart(const std::unique_ptr<CommandDTO>& dto);
    std::vector<char> serializeShooting(const std::unique_ptr<CommandDTO>& dto);
    std::vector<char> serializeSwitchWeapon(const std::unique_ptr<CommandDTO>& dto);
    std::vector<char> serializeGamesList(const std::unique_ptr<GamesListDTO>& dto);
    std::vector<char> serializeGameDTO(const std::unique_ptr<GameDTO> dto);
    std::vector<char> serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto);
    std::vector<char> serializeEnemyDTO(const std::unique_ptr<EnemyDTO> dto);
    std::vector<char> serializeBulletDTO(const std::unique_ptr<BulletDTO> dto);
    std::vector<char> serializeItemDTO(const std::unique_ptr<ItemDTO> dto);
    std::vector<char> serializeWeaponDTO(const std::unique_ptr<WeaponDTO> dto);
    std::vector<char> serializeTileDTO(const std::unique_ptr<TileDTO> dto);


    Serializer() {}
    explicit Serializer(std::shared_ptr<Socket> socket);
    void sendId(int32_t id);
    void sendCommand(const std::unique_ptr<CommandDTO> dto, bool& wasClosed);
    void sendGameDTO(const std::unique_ptr<GameDTO> dto);
};


#endif  // SERIALIZER_H
