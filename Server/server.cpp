#include "server.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <stdexcept>
#include "../Server/client_acceptor.h"

Server::Server(std::string& servname) 
    : servname(servname)
      {}

void Server::run(){

    ClientAcceptor clientAcceptorThread(servname);

    clientAcceptorThread.start();

    while (std::cin.get() != 'q') {}

    clientAcceptorThread.stop();
    clientAcceptorThread.join();
    //shutdown();
}


