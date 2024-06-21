#ifndef MAPS_MANAGER_H_
#define MAPS_MANAGER_H_

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "yaml-cpp/yaml.h"

class MapsManager {
private:
    uint8_t nextId_ = 0;
    // mapId -> [mapName, mapFilePath]
    std::unordered_map<uint8_t, std::pair<std::string, std::string>> maps_;
    std::unordered_map<std::string, bool> loadedMaps_;

    static MapsManager* instance;
    MapsManager();
    static void loadMaps(MapsManager* ins);
    static MapsManager* getInstance();

public:
    static void updateMaps();
    static std::string getMapNameById(const uint8_t& id);
    static std::string getMapFileNameById(const uint8_t& id);
    static std::unordered_map<uint8_t, std::string> getMapIdAndName();
};

#endif  // MAPS_MANAGER_H_
