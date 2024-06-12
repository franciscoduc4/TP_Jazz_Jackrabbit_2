#ifndef MAPS_MANAGER_H_
#define MAPS_MANAGER_H_

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "yaml-cpp/yaml.h"  // Assuming you have yaml-cpp installed

class MapsManager {
public:
    void loadMaps() {
        const std::filesystem::path mapsdir = "../../maps";
        for (const auto& entry: std::filesystem::directory_iterator(mapsdir)) {
            std::string filepath = entry.path().string();
            int id = nextId_++;
            std::string name = entry.path().filename().string();

            YAML::Node config = YAML::LoadFile(filepath);

            // Assume the YAML file has a "name" field
            // if (config["name"]) {
            // name = config["name"].as<std::string>();
            // }

            maps_.emplace(id, name);
        }
    }

    std::string getMapDataById(int mapId) const { return maps_.at(mapId); }

    std::map<int, std::string> getEpisodes() const {
        std::map<int, std::string> episodes;
        for (const auto& [id, mapName]: maps_) {
            episodes[id] = mapName;
        }
        return episodes;
    }

private:
    int nextId_ = 0;
    std::unordered_map<int, std::string> maps_;
};

#endif  // MAPS_MANAGER_H_
