#include "mapsList.h"

MapsListDTO::MapsListDTO(): CommandDTO(Command::MAPS_LIST) {}

MapsListDTO::MapsListDTO(std::unordered_map<uint8_t, std::string> maps):
        CommandDTO(Command::MAPS_LIST) {
    for (const auto& [id, mapName]: maps) {
        mapsMap[id] = mapName;
    }
}

std::unordered_map<uint8_t, std::string> MapsListDTO::getMapsMap() const { return mapsMap; }

std::unordered_map<int, std::string> MapsListDTO::getMaps() const {
    std::unordered_map<int, std::string> maps;
    for (const auto& [id, mapName]: mapsMap) {
        maps[static_cast<int>(id)] = mapName;
    }
    return maps;
}
