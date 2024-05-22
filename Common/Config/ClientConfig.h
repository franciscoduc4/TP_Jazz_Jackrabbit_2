#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>
#include <yaml-cpp/yaml.h>

#include "Common/logger.h"

class ClientConfig {
 private:
    static ClientConfig* instance;
    Logger logger;
    YAML::Node root;
    ClientConfig();
    static std::string getLogFile();
 public:
    static ClientConfig* getInstance();
    Logger& getLogger();
    static void deleteInstance();
};

#endif  // __CLIENT_CONFIG_H__
