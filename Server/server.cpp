#include "server.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "acceptorThread.h"
#include "gamesMonitor.h"

Server::Server(std::string& servname): servname(servname), gamesMonitor() {}

void Server::run() {
    ClientAcceptor clientAcceptorThread(servname, gamesMonitor);

    clientAcceptorThread.start();

    while (std::cin.get() != 'q') {}

    clientAcceptorThread.stop();
    clientAcceptorThread.join();
    shutdown();
}
