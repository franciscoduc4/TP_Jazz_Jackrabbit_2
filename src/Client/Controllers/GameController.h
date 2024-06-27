#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include <vector>

#include "../../Common/DTO/dto.h"
#include "../../Common/Types/command.h"
#include "../../Common/Types/weapon.h"
#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

class GameController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue;

public:
    GameController(Serializer& serializer, Deserializer& deserializer,
                   std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue);

    void idle_msg(uint8_t playerId);

    void sendMsg(uint8_t playerId, Command& cmd, std::vector<uint8_t>& parameters);

    void move_msg(uint8_t playerId, std::vector<uint8_t>& parameters);

    void shoot_msg(uint8_t playerId);

    void switch_weapon_msg(uint8_t playerId, std::vector<uint8_t>& parameters);

    void sprint(uint8_t playerId);

    void cheat(const std::vector<uint8_t>& parameters);

    std::unique_ptr<DTO> getServerMsg();
};

#endif  // GAMECONTROLLER_H
