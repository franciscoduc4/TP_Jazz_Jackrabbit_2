#ifndef COMMAND_DTO_H_
#define COMMAND_DTO_H_

#include <cstdint>
#include <vector>

#include "../Types/elements.h"


class GameElementDTO {
private:
    ElementType type;

    int32_t playerId;
    uint16_t x;
    uint16_t y;
    bool isVisible;

public:
    GameElementDTO();

    explicit GameElementDTO(ElementType element);

    GameElementDTO(int32_t& playerId, ElementType element);

    ElementType getElementType();

    int getPlayerId();

    std::pair<uint16_t, uint16_t> getPosition();

    bool getVisibility();

    virtual ~GameElementTypeDTO() {}
};
#endif  // COMMAND_DTO_H_
