#include "server.h"


Server::Server(std::string& servname): servname(servname), gameMonitor() {}

void Server::run() {
    AcceptorThread acceptor(servname, gameMonitor);

    acceptor.start();

    while (std::cin.get() != 'q') {}

    acceptor.stop();
    acceptor.join();
    shutdown();
}
