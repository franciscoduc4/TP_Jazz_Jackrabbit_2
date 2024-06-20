#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <atomic>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/gameCommand.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/lobby.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/DTO/gameUpdate.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

class Serializer {
private:
    std::shared_ptr<Socket> socket;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    bool wasClosed;

    static void insertGameInfoIntoBuffer(std::vector<char>& buffer, const GameInfo& gameInfo);
    static void insertPositionIntoBuffer(std::vector<char>& buffer, const uint32_t& x, const uint32_t& y);
    static void insert_int_into_buffer(std::vector<char>& buffer, const int& value);

    void clientClosed();
public:
    // Lobby
    static std::vector<char> serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto);
    static std::vector<char> serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto);
    static std::vector<char> serializeGamesList(const std::unique_ptr<GamesListDTO>& dto);
    static std::vector<char> serializeGameUpdate(const std::unique_ptr<GameUpdateDTO>& dto);
    static std::vector<char> serializeMapsList(const std::unique_ptr<MapsListDTO>& dto);
    // Game
    static std::vector<char> serializePlayerDTO(const std::unique_ptr<PlayerDTO>& dto);
    static std::vector<char> serializeEnemyDTO(const std::unique_ptr<EnemyDTO>& dto);
    static std::vector<char> serializeBulletDTO(const std::unique_ptr<BulletDTO>& dto);
    static std::vector<char> serializeItemDTO(const std::unique_ptr<ItemDTO>& dto);
    static std::vector<char> serializeWeaponDTO(const std::unique_ptr<WeaponDTO>& dto);
    static std::vector<char> serializeTileDTO(const std::unique_ptr<TileDTO>& dto);

    Serializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame);
    void sendId(uint8_t id);
    void sendCommand(const std::unique_ptr<CommandDTO>& dto);
    void sendGameDTO(const std::unique_ptr<GameDTO>& dto);
};


#endif  // SERIALIZER_H
