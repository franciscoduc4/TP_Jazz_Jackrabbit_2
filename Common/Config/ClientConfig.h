#ifndef __CLIENT_CONFIG_H__
#define __CLIENT_CONFIG_H__

#include <string>
#include <yaml-cpp/yaml.h>

class ClientConfig {
 private:
    static ClientConfig* instance;
    YAML::Node root;
    ClientConfig();
 public:
    static ClientConfig* getInstance();
    static std::string getLogFile();
    static void deleteInstance();
};

#endif  // __CLIENT_CONFIG_H__
