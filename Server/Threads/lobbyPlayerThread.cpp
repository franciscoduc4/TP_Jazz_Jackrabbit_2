#include "lobbyPlayerThread.h"
#include <utility>
#include "../Common/protocol.h"

LobbyPlayerThread::LobbyPlayerThread(Player&& player, GameMonitor& gameMonitor):
        player(std::move(player)), 
        gameMonitor(gameMonitor), 
        inLobby(true), 
        protocol(player.getSocketRef()) {}


void LobbyPlayerThread::run() {
    
    try {
        while (inLobby) {
            // TODO: esperar a que el cliente envíe un mensaje de inicio de juego
            ProtocolMessage command = protocol.recvMessage();
            // LobbyCommand lobbyCommand = LobbyCommand::getCommand(command);

            // lobbyCommand.exec(gameMonitor, std::move(player));

            // if (inGame) {}
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

