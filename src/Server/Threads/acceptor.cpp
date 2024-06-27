#include "acceptor.h"
#include <memory>

/*
 * Constructor de AcceptorThread.
 * Inicializa el socket del servidor, el monitor de la cola, el monitor del juego y la lista de jugadores.
 */
AcceptorThread::AcceptorThread(const std::string& servname):
        serverSocket(std::make_shared<Socket>(servname.c_str())),
        queueMonitor(),
        gameMonitor(queueMonitor),
        players() {}

/*
 * Método run del hilo de aceptación.
 * Escucha nuevas conexiones de jugadores, crea nuevos jugadores y los agrega al monitor del juego.
 * También elimina jugadores que ya no están jugando.
 */
void AcceptorThread::run() {
    while (isAlive) {
        try {
            auto playerSocket = std::make_shared<Socket>(serverSocket->accept());
            std::cout << "New player connected" << std::endl;
            if (!isAlive) {
                break;
            }

            auto player = std::make_unique<Player>(std::move(playerSocket), gameMonitor,
                                                   static_cast<uint8_t>(players.size()));
            gameMonitor.addPlayerRecvQueue(player->getPlayerId(), player->getRecvQueue());
            players.emplace_back(std::move(player));
            removeDeadPlayers();
        } catch (const std::exception& e) {
            if (isAlive) {
                std::cerr << e.what() << std::endl;
            }
            removeAllPlayers();
        }
    }
}

/*
 * Método stop del hilo de aceptación.
 * Detiene el hilo, cierra el socket del servidor, finaliza todos los juegos y desconecta a todos los jugadores.
 */
void AcceptorThread::stop() {
    removeAllPlayers();
    isAlive.store(false);
    serverSocket->shutdown(SHUT_RDWR);
    serverSocket->close();
    gameMonitor.endAllGames();
    _keep_running = false;
    std::cout << "Acceptor stopped" << std::endl;
}

/*
 * Método removeDeadPlayers del hilo de aceptación.
 * Elimina de la lista a los jugadores que ya no están jugando.
 */
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

/*
 * Método removeAllPlayers del hilo de aceptación.
 * Desconecta y elimina a todos los jugadores de la lista.
 */
void AcceptorThread::removeAllPlayers() {
    for (auto& player: players) {
        player->disconnect();
    }
    players.clear();
}
