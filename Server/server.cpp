#include "server.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "Game/gameMonitor.h"

#include "acceptorThread.h"

Server::Server(std::string& servname): servname(servname), gamesMonitor() {}

void Server::run() {
    AcceptorThread acceptor(servname, gamesMonitor);

    acceptor.start();

    while (std::cin.get() != 'q') {}

    acceptor.stop();
    acceptor.join();
    shutdown();
}
