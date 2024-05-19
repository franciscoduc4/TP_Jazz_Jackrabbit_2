#include <exception>
#include <iostream>
#include <sstream>

#include "../Common/logger.h"
#include "../Common/Config/ServerConfig.h"

#define SUCCESS 0
#define FAIL -1
#define SERVER_ARGS 2

int main(int argc, char* argv) {
    Logger logger(ServerConfig::getLogFile());
    if (argc != SERVER_ARGS) {
        logger.error(__func__, __LINE__, "Invalid number of arguments. Expected: %d, got: %d",
                     SERVER_ARGS, argc);
        return FAIL;
    }
    try {
        // Init Server con Logger.
    } catch (const std::exception& e) {
        logger.error(__func__, __LINE__, "Exception caught: %s", e.what());
        return FAIL;
    }
    return SUCCESS;
}
