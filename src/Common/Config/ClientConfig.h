#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>
#include <vector>

#include "../logger.h"
#include <yaml-cpp/yaml.h>


class ClientConfig {
private:
    static ClientConfig* instance;
    YAML::Node root;
    ClientConfig();
    static std::string getLogFile();

public:
    static ClientConfig* getInstance();
    Logger& getLogger();
    // Files
    static std::string getEpisodeFile();
    static std::string getCharacterSelectFile();
    static std::string getJazzFile();
    static std::string getSpazFile();
    static std::string getLoriFile();
    static std::string getTurtleFile();
    static std::string getSFXFile();
    static std::string getItemsFile();
    // Colour Keys
    static std::tuple<int, int, int> getEpisodesColourKey();
    static std::tuple<int, int, int> getCharacterSelectColourKey();
    static std::tuple<int, int, int> getJazzColourKey();
    static std::tuple<int, int, int> getSpazColourKey();
    static std::tuple<int, int, int> getLoriColourKey();
    static std::tuple<int, int, int> getTurtleColourKey();
    static std::tuple<int, int, int> getSFXColourKey();
    static std::tuple<int, int, int> getItemsColourKey();
    // Rectangular Sprites
    static std::vector<std::vector<int>> getEpisodesSprites();
    // Sprites
    static std::vector<std::vector<std::pair<int, int>>> getJazzSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getJazzSelectSprites();
    static std::vector<std::vector<std::pair<int, int>>> getSpazSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getSpazSelectSprites();
    static std::vector<std::vector<std::pair<int, int>>> getLoriSelectNameSprites();
    static std::vector<std::vector<std::pair<int, int>>> getLoriSelectSprites();
    // Delete Instance
    static void deleteInstance();
};

#endif  // __CLIENT_CONFIG_H__
