#include <iostream>
#include <sstream>
#include <utility>
#include "sys/socket.h"

ClientAcceptor::ClientAcceptor(std::string& servname):
        serverSocket(servname.c_str()) {}

void ClientAcceptor::run() {

    while (isAlive) {
        try {
            Socket playerSocket = serverSocket.accept();
            playerHandlers.emplace_back(std::make_unique<PlayerHandler>(std::move(playerSocket)), gameMonitor, actionQueue);

            playerHandlers.back()->start();
            cleanUpInactiveHandlers();

            //Agregar player a un juego
        } catch (const std::exception& e) {
            cleanUpAllHandlers();
            if (isAlive){
                std::cerr << e.what() << std::endl;
            }

        }
    }
}

void ClientAcceptor::stop() {
    cleanUpAllHandlers();
    isAlive = false;
    serverSocket.shutdown(SHUT_RDWR);
    serverSocket.close();
}

void ClientAcceptor::cleanUpInactiveHandlers() {
    auto it = clientHandlers.begin();
    while (it != clientHandlers.end()) {
        if (!(*it)->isAlive()) {
            (*it)->stop();
            (*it)->join();
            it = clientHandlers.erase(it);
        } else {
            ++it;
        }
    }
}

void ClientAcceptor::cleanUpAllHandlers() {
    auto it = clientHandlers.begin();
    while (it != clientHandlers.end()) {
        (*it)->stop();
        (*it)->join();
        it = clientHandlers.erase(it);
    }
    clientHandlers.clear();
}
