#ifndef GAME_ELEMENT_DTO_H_
#define GAME_ELEMENT_DTO_H_

#include <cstdint>
#include <utility>
#include <vector>
#include <memory>

#include "../Types/dto.h"
#include "../Types/elements.h"
#include "dto.h"


class GameElementDTO : public DTO {
private:
    ElementType type;

    uint8_t playerId;
    uint16_t x;
    uint16_t y;
    bool isVisible;

    DTOType dtoType = DTOType::GAME_ELEMENT_DTO;


public:
    GameElementDTO();

    explicit GameElementDTO(ElementType element);

    GameElementDTO(uint8_t& playerId, ElementType element);

    DTOType getType() const;
    ElementType getElementType() const;

    int getPlayerId() const;

    std::pair<uint16_t, uint16_t> getPosition();

    bool getVisibility();

    virtual std::unique_ptr<DTO> clone() const override;

    virtual ~GameElementDTO();
};

#endif  // COMMAND_DTO_H_
