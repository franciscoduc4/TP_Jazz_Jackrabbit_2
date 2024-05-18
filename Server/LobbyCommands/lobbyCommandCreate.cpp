#include "lobbyCommandCreate.h"
#include <utility>

void LobbyCommandsCreate::exec(GameMonitor& gameMonitor, Player&& player) {
    gameMonitor.createGame(player.getGameName(), 5, std::move(player));
}
