#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../../Common/DTO/lobby.h"
#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/move.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

#include <vector>
#include <memory>
#include <string>
#include <map>

class Serializer {
    private:
        std::shared_ptr<Socket> socket;

        std::vector<char> serializeCreateGame(const CreateGameDTO& dto);
        std::vector<char> serializeJoinGame(const JoinGameDTO& dto);
        std::vector<char> serializeGamesList(const CommandDTO& dto);
        std::vector<char> serializeMove(const MoveDTO& dto);
        std::vector<char> serializeStart(const CommandDTO& dto);
        std::vector<char> serializeShooting(const CommandDTO& dto);
        std::vector<char> serializeReloading(const CommandDTO& dto);
        std::vector<char> serializeSwitchWeapon(const CommandDTO& dto);
        void serializeGamesList(const std::map<int32_t, std::string>& map, 
        std::vector<char>& buffer);
        std::vector<char> serializeGameDTO(const std::unique_ptr<GameDTO>dto);
        std::vector<char> serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto);
        std::vector<char> serializeEnemyDTO(const std::unique_ptr<EnemyDTO> dto);
        std::vector<char> serializeBulletDTO(const std::unique_ptr<BulletDTO> dto);
        std::vector<char> serializeItemDTO(const std::unique_ptr<ItemDTO> dto);
        std::vector<char> serializeWeaponDTO(const std::unique_ptr<WeaponDTO> dto);
        std::vector<char> serializeTileDTO(const std::unique_ptr<TileDTO> dto);
        std::vector<char> serializeSprite(const std::unique_ptr<Sprite> sprite);


    public:
        Serializer() {}
        explicit Serializer(std::shared_ptr<Socket> socket);
        void sendCommand(const CommandDTO& dto, bool& wasClosed);
        void sendCreateGame(const CreateGameDTO& dto);
        void sendJoinGame(const JoinGameDTO& dto);
        void sendGamesList(const CommandDTO& dto);
        void sendCharacterType(const CharacterTypeDTO& dto);
        void sendMove(const MoveDTO& dto);
        void sendStart(const CommandDTO& dto);
        void sendShooting(const CommandDTO& dto);
        void sendReloading(const CommandDTO& dto);
        void sendSwitchWeapon(const CommandDTO& dto);
        void sendId(int32_t id);
        void sendGameDTO(const std::unique_ptr<GameDTO> dto);
        void sendLobbyDTO(const std::unique_ptr<LobbyDTO> dto);

};


#endif //SERIALIZER_H
