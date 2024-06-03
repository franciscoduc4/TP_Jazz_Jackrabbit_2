#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>
#include <yaml-cpp/yaml.h>
#include <vector>

#include "../logger.h"

class ClientConfig {
 private:
    static ClientConfig* instance;
    YAML::Node root;
    ClientConfig();
    static std::string getLogFile();
 public:
    static ClientConfig* getInstance();
    Logger& getLogger();
    static std::string getEpisodeFile();
    static std::vector<std::vector<int>> getEpisodesSprites();
    static void deleteInstance();
};

#endif  // __CLIENT_CONFIG_H__
