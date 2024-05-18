#include "acceptorThread.h"

#include <iostream>
#include <sstream>
#include <utility>
#include <sys/socket.h>
#include "../Common/socket.h"

AcceptorThread::AcceptorThread(const std::string& servname, GameMonitor& gameMonitor):
        serverSocket(servname.c_str()), gameMonitor(), lobbyPlayers() {}

void AcceptorThread::run() {
    while (isAlive) {
        try {
            Socket playerSocket = serverSocket.accept();
            if (!isAlive) {
                break;
            }
            Player player(std::move(playerSocket));
            movePlayerToLobby(std::move(player), gameMonitor);

            //cleanLobby();
        } catch (const std::exception& e) {
            if (isAlive) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void AcceptorThread::stop() {
    isAlive = false;
    serverSocket.shutdown(SHUT_RDWR);
    serverSocket.close();
}

void AcceptorThread::movePlayerToLobby(Player&& player, GameMonitor& gameMonitor) {
    LobbyPlayerThread lobbyPlayer(std::move(player), gameMonitor);
    lobbyPlayers.emplace_back(lobbyPlayer);
    lobbyPlayers.back().start();
}

void AcceptorThread::cleanLobby() {
    for (auto& lobbyPlayer : lobbyPlayers) {
        lobbyPlayer.stop();
        lobbyPlayer.join();
    }
    lobbyPlayers.clear();
}

