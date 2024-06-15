#ifndef MAPS_LIST_H
#define MAPS_LIST_H

#include <string>
#include <unordered_map>
#include <vector>

#include "command.h"

class MapsListDTO: public CommandDTO {
private:
    std::unordered_map<uint8_t, std::string> mapsMap;

public:
    MapsListDTO();
    explicit MapsListDTO(std::unordered_map<uint8_t, std::string> maps);

    std::unordered_map<uint8_t, std::string> getMapsMap() const;
    // TODO: check si se usa.
    std::unordered_map<int, std::string> getMaps() const;
};

#endif  // MAPS_LIST_H
