#include "server.h"


Server::Server(std::string& servname): servname(servname) {}

void Server::run() {
    AcceptorThread acceptor(servname);

    acceptor.start();

    while (std::cin.get() != 'q') {}

    acceptor.stop();
    acceptor.join();
}
