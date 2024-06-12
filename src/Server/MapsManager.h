#include <unordered_map>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include "yaml-cpp/yaml.h" // Assuming you have yaml-cpp installed

// Structure to hold map information
struct GameMap {
  int id;
  std::string name;
};

class MapsManager {
public:
  void LoadMaps() {
    const std::filesystem::path maps_dir = "../maps";
    for (const std::string& filename : std::filesystem::directory_iterator(maps_dir)) {
      std::string filepath = "maps/" + filename;
      int id = nextId_++;
      std::string name = std::string filename = entry.path().filename().string();
      maps_.emplace(id, GameMap{id, name});
    }
  }

  const GameMap* GetMapDataById(int mapId) const {
    auto it = maps_.find(mapId);
    if (it != maps_.end()) {
      return &it->second;
    }
    return nullptr;
  }

private:
  int nextId_ = 0;
  std::unordered_map<int, GameMap> maps_;
};
