#include "mapsManager.h"

#include <iostream>

const static std::string MAPS_DIR = "../src/maps";  // Ajusta la ruta relativa aquí

MapsManager* MapsManager::instance = nullptr;

MapsManager::MapsManager():
        nextId_(0),
        maps_(std::unordered_map<uint32_t, std::pair<std::string, std::string>>()),
        loadedMaps_(std::unordered_map<std::string, bool>()) {}

MapsManager* MapsManager::getInstance() {
    if (instance == nullptr) {
        instance = new MapsManager();
        try {
            loadMaps(instance);
        } catch (const std::exception& e) {
            std::cerr << "Exception caught in MapsManager::getInstance: " << e.what() << std::endl;
            delete instance;
            instance = nullptr;
            throw;
        }
    }
    return instance;
}

void MapsManager::loadMaps(MapsManager* ins) {
    const std::filesystem::path mapsdir = MAPS_DIR;
    if (!std::filesystem::exists(mapsdir)) {
        throw std::runtime_error("Directory does not exist: " + mapsdir.string());
    }
    for (const auto& entry: std::filesystem::directory_iterator(mapsdir)) {
        if (entry.is_directory())
            continue;
        if (ins->loadedMaps_.find(entry.path().filename().string()) != ins->loadedMaps_.end()) {
            continue;
        }
        uint32_t id = ins->nextId_++;
        std::string filepath = entry.path().string();
        std::string name = entry.path().filename().string();
        std::pair<std::string, std::string> mapData = std::make_pair(name, filepath);

        ins->maps_.emplace(id, mapData);
        ins->loadedMaps_.emplace(name, true);
    }
}

void MapsManager::updateMaps() {
    MapsManager* thisInstance = getInstance();
    loadMaps(thisInstance);
}

std::string MapsManager::getMapNameById(const uint32_t& id) {
    MapsManager* thisInstance = getInstance();
    if (thisInstance->maps_.find(id) == thisInstance->maps_.end()) {
        return "";
    }
    return thisInstance->maps_[id].first;
}

std::string MapsManager::getMapFileNameById(const uint32_t& id) {
    MapsManager* thisInstance = getInstance();
    if (thisInstance->maps_.find(id) == thisInstance->maps_.end()) {
        return "";
    }
    return thisInstance->maps_[id].second;
}

std::unordered_map<uint32_t, std::string> MapsManager::getMapIdAndName() {
    MapsManager* thisInstance = getInstance();
    std::unordered_map<uint32_t, std::string> mapIdAndName;
    for (const auto& map: thisInstance->maps_) {
        mapIdAndName.emplace(map.first, map.second.first);
    }
    return mapIdAndName;
}
