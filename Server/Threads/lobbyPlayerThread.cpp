#include "lobbyPlayerThread.h"
#include <utility>

LobbyPlayerThread::LobbyPlayerThread(Player&& player, GameMonitor& gameMonitor):
        player(std::move(player)), gameMonitor(gameMonitor), inLobby(true) {}


void LobbyPlayerThread::run() {
    bool inGame = false;

    try {
        while (!inGame) {
            // TODO: esperar a que el cliente envíe un mensaje de inicio de juego
            // Command command = protocol.recvCommand();
            // LobbyCommand lobbyCommand = LobbyCommand::getCommand(command);

            // lobbyCommand.exec(gameMonitor, std::move(player));

            // if (inGame) {}
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}