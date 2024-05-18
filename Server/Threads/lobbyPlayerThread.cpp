#include "lobbyPlayerThread.h"

#include <utility>

#include "../Common/protocol.h"
#include "../LobbyCommands/lobbyCommand.h"

LobbyPlayerThread::LobbyPlayerThread(Player&& player, GameMonitor& gameMonitor):
        player(std::move(player)),
        gameMonitor(gameMonitor),
        inLobby(true),
        protocol(player.getSocketRef()) {}


void LobbyPlayerThread::run() {
    try {
        while (inLobby) {
            ProtocolMessage message = protocol.recvMessage();
            auto lobbyCommand = LobbyCommand::getCommand(message);
            ProtocolMessage res = lobbyCommand->exec(gameMonitor, std::move(player), inLobby);
            if (res.cmd != 0x00) {
                protocol.sendMessage(res);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool LobbyPlayerThread::isInLobby() const { return inLobby; }