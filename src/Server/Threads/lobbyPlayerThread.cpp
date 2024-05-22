#include "lobbyPlayerThread.h"
#include <memory>
#include <utility>

LobbyPlayerThread::LobbyPlayerThread(Socket&& playerSocket, GameMonitor& gameMonitor):
        protocol(std::move(playerSocket)), gameMonitor(gameMonitor), inLobby(true) {}

void LobbyPlayerThread::run() {
    try {
        while (inLobby) {
            ProtocolMessage message = protocol.recvMessage();
            auto lobbyCommand = LobbyCommand::getCommand(message);
            handleCommand(protocol, lobbyCommand);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool LobbyPlayerThread::isInLobby() const { return inLobby; }

void LobbyPlayerThread::handleCommand(Protocol& protocol,
                                      const std::unique_ptr<LobbyCommand>& lobbyCommand) {
    ProtocolMessage res = lobbyCommand->exec(gameMonitor, std::move(protocol), inLobby);
    if (res.cmd != 0x00) {
        protocol.sendMessage(res);
    }
}

void LobbyPlayerThread::stop() { inLobby = false; }

