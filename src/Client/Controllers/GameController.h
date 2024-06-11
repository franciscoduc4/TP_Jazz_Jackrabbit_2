#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"
#include "../../Common/Types/command.h"
#include "../../Common/DTO/dto.h"

class GameController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue;
public:
    GameController(Serializer& serializer, Deserializer& deserializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue);

    void sendMsg(int32_t playerId, Command& cmd, std::vector<uint8_t>& parameters);

    void move_msg(int32_t playerId, std::vector<uint8_t>& parameters);

    void shoot_msg(int32_t playerId);

    std::unique_ptr<DTO> getServerMsg();
	
};

#endif  // GAMECONTROLLER_H
