#include <exception>
#include <iostream>
#include <sstream>

#include "../Common/Config/ServerConfig.h"
#include "../Common/logger.h"
#include "server.h"

#define SUCCESS 0
#define FAIL -1
#define SERVER_ARGS 2

int main(int argc, char** argv) {
    if (argc != SERVER_ARGS) {
        std::cerr << "Invalid number of arguments. Expected: " << 
        SERVER_ARGS << ", got: " << argc << std::endl;
        return FAIL;
    }

    //const std::string configPath = "../src/config/server.yaml";
    
    try {
        //ServerConfig::loadConfig(configPath);
        //Logger logger(ServerConfig::getLogFile());
        Server server(argv[1]);
        server.run();
        // Init Server with Logger.
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return FAIL;
    }
    return SUCCESS;
}
