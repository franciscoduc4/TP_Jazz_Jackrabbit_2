#include "mapsList.h"

#include <map>
#include <string>
#include <utility>

#include "../../../Common/maps/mapsManager.h"

MapsListHandler::MapsListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

void MapsListHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                              std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                              std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    gameMonitor.mapsList(sendQueue);
}
