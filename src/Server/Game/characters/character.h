#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/DTO/player.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/direction.h"
#include "../../../Common/Types/entity.h"
#include "../../../Common/vector.h"
#include "../entity.h"
#include "../movements/movement.h"
#include "../positions/position.h"

class Character: public Entity {
private:
    CharacterType type;
    std::shared_ptr<Position> position;
    Movement movement;

public:
    explicit Character(uint8_t playerId, CharacterType type, Vector<uint32_t> position);
    void update(Direction direction);
    void move();

    PlayerDTO getDTO() const;
};

#endif  // CHARACTER_H_