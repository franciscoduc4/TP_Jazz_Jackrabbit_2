#include "acceptor.h"


AcceptorThread::AcceptorThread(const std::string& servname):
        serverSocket(std::make_shared<Socket>(servname.c_str())),
        queueMonitor(),
        gameMonitor(queueMonitor),
        players() {}

void AcceptorThread::run() {
    while (isAlive) {
        try {
            Socket playerSocket = serverSocket->accept();
            std::cout << "New player connected" << std::endl;
            if (!isAlive) {
                break;
            }
            auto player = std::make_unique<Player>(playerSocket, gameMonitor, queueMonitor,
                                                   static_cast<uint8_t>(players.size()));
            players.emplace_back(std::move(player));
            removeDeadPlayers();
        } catch (const std::exception& e) {
            if (isAlive) {
                std::cerr << e.what() << std::endl;
            }
            removeAllPlayers();
            gameMonitor.endAllGames();
        }
    }
}

void AcceptorThread::stop() {
    removeAllPlayers();
    gameMonitor.endAllGames();
    isAlive = false;
    serverSocket->shutdown(SHUT_RDWR);
    serverSocket->close();
}

void AcceptorThread::removeDeadPlayers() {
    for (auto it = players.begin(); it != players.end();) {
        if (!(*it)->isPlaying()) {
            (*it)->disconnect();
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void AcceptorThread::removeAllPlayers() {
    for (auto& player: players) {
        player->disconnect();
    }
    players.clear();
}