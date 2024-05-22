#include "Common/Config/ClientConfig.h"

#include <unistd.h> 

const static std::string YAML_FILE_PATH = "config/client.yaml";

ClientConfig* ClientConfig::instance = nullptr;

ClientConfig::ClientConfig() {
    this->root = YAML::LoadFile(YAML_FILE_PATH);
    this->logger = Logger(this->getLogFile());
}

ClientConfig* ClientConfig::getInstance() {
    if (instance == nullptr) {
        instance = new ClientConfig();
    }
    return instance;
}

std::string ClientConfig::getLogFile() {
    std::string logFile = getInstance()->root["LOG_FILE"].as<std::string>();
    std::size_t pos = logFile.find(".log");
    if (pos != std::string::npos) {
        std::ostringstream pidStream;
        pidStream << getpid();
        logFile.insert(pos, "_" + pidStream.str());
    }
    return logFile;
}

Logger& ClientConfig::getLogger() {
    return getInstance()->logger;
}

void ClientConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
