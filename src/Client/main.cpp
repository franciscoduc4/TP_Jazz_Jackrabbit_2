#include <exception>
#include <iostream>
#include <sstream>

#include "../Common/Config/ClientConfig.h"
#include "../Common/logger.h"

#include "client.h"

#define SUCCESS 0
#define FAIL -1
#define CLIENT_ARGS 3

int main(int argc, char* argv[]) {
    if (argc != CLIENT_ARGS) {
        std::cerr << "Invalid number of arguments. Expected: " << CLIENT_ARGS << ", got: " << argc << std::endl;
        return FAIL;
    }
    try {
        Client client(argv[1], argv[2]);
        client.start();
    } catch (const std::exception& e) {
        ClientConfig::deleteInstance();
        return FAIL;
    }
  
    ClientConfig::deleteInstance();
  
    return SUCCESS;
}
