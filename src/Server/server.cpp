#include "server.h"

Server::Server(const std::string& servname): servname(servname.c_str()) {}

void Server::run() {
    AcceptorThread acceptor(servname);

    acceptor.start();

    while (std::cin.get() != 'q') {}

    acceptor.stop();
    acceptor.join();
}
