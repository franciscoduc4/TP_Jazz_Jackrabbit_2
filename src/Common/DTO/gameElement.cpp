#include "gameElement.h"

GameElementDTO::GameElementDTO() {}

GameElementDTO::GameElementDTO(ElementType element): type(element) {}

GameElementDTO::GameElementDTO(uint8_t& playerId, ElementType element):
        playerId(playerId), type(element) {}

ElementType GameElementDTO::getElementType() const { return type; }

int GameElementDTO::getPlayerId() const { return playerId; }

std::pair<uint16_t, uint16_t> GameElementDTO::getPosition() { return std::make_pair(x, y); }

bool GameElementDTO::getVisibility() { return isVisible; }

GameElementDTO::~GameElementDTO() {}
