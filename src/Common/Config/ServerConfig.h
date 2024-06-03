#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <string>
#include <yaml-cpp/yaml.h>

class ServerConfig {
 private:
    static ServerConfig* instance;
    YAML::Node root;
    ServerConfig();
 public:
    static ServerConfig* getInstance();
    static std::string getLogFile();
    static void deleteInstance();
};

#endif  // __SERVER_CONFIG_H__
