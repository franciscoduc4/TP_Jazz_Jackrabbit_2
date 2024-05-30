#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../../Common/DTO/characterType.h"
#include "../../Common/DTO/command.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/move.h"
#include "../../Common/Types/command.h"
#include "../../Common/socket.h"

#include <vector>
#include <memory>

class Serializer {
    private:
        std::shared_ptr<Socket> socket;

        std::vector<char> serializeCreateGame(const CreateGameDTO& dto);
        std::vector<char> serializeJoinGame(const JoinGameDTO& dto);
        std::vector<char> serializeGamesList(const CommandDTO& dto);
        std::vector<char> serializeCharacterType(const CharacterTypeDTO& dto);
        std::vector<char> serializeMove(const MoveDTO& dto);
        std::vector<char> serializeStart(const CommandDTO& dto);
        std::vector<char> serializeShooting(const CommandDTO& dto);
        std::vector<char> serializeReloading(const CommandDTO& dto);
        std::vector<char> serializeSwitchWeapon(const CommandDTO& dto);

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


};


#endif //SERIALIZER_H
