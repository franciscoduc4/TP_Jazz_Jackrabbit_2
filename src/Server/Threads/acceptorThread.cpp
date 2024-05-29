#include "acceptorThread.h"


AcceptorThread::AcceptorThread(const std::string& servname):
        serverSocket(servname.c_str()), gameMonitor(), lobbyPlayers() {}

void AcceptorThread::run() {
    while (isAlive) {
        try {
            Socket playerSocket = serverSocket.accept();
            std::cout << "New player connected" << std::endl;
            if (!isAlive) {
                break;
            }
            movePlayerToLobby(std::move(playerSocket), gameMonitor);
            cleanInactiveLobbyPlayers();
        } catch (const std::exception& e) {
            if (isAlive) {
                std::cerr << e.what() << std::endl;
            }
            cleanLobby();
        }
    }
}

void AcceptorThread::stop() {
    cleanLobby();
    isAlive = false;
    serverSocket.shutdown(SHUT_RDWR);
    serverSocket.close();
}

void AcceptorThread::movePlayerToLobby(Socket&& playerSocket, GameMonitor& gameMonitor) {
    lobbyPlayers.emplace_back(
            std::make_unique<LobbyPlayerThread>(std::move(playerSocket), gameMonitor));
    lobbyPlayers.back()->start();
}

void AcceptorThread::cleanInactiveLobbyPlayers() {
    auto it = lobbyPlayers.begin();
    while (it != lobbyPlayers.end()) {
        if (!(*it)->isInLobby()) {
            (*it)->stop();
            (*it)->join();
            it = lobbyPlayers.erase(it);
        } else {
            ++it;
        }
    }
}

void AcceptorThread::cleanLobby() {
    auto it = lobbyPlayers.begin();
    while (it != lobbyPlayers.end()) {
        (*it)->stop();
        (*it)->join();
        it = lobbyPlayers.erase(it);
    }
}
