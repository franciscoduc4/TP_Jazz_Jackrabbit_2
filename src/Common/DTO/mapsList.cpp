#include "mapsList.h"

#include <iostream>

MapsListDTO::MapsListDTO(): CommandDTO(Command::MAPS_LIST) {}

MapsListDTO::MapsListDTO(std::unordered_map<uint8_t, std::string> maps):
        CommandDTO(Command::MAPS_LIST) {
    for (const auto& [id, mapName]: maps) {
        mapsMap[id] = mapName;
        std::cout << "Map ID: " << (int)id << " Map Name: " << mapName << std::endl;
    }
}

std::unordered_map<uint8_t, std::string> MapsListDTO::getMapsMap() const { return mapsMap; }
