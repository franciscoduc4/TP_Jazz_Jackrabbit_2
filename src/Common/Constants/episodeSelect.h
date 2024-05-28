#ifndef EPISODE_SELECT_H
#define EPISODE_SELECT_H

#include <cstdint>

enum class EpisodeSelect : uint8_t {
    INVALID = 0x00,
    FORMERLY_PRINCE = 0x01,
    JAZZ_IN_TIME,
    FLASHBACK,
    FUNKY_MONEYS,
    SHAREWARE_DEMO,
    HOME_COOKED_LEVELS,
    THE_CHRISTMAS_CHRONICLES,
    THE_SECRET_FILES
};

#endif  // EPISODE_SELECT_H
