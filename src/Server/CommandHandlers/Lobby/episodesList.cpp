#include "episodesList.h"

#include <map>
#include <string>
#include <utility>

#include "../../Game/mapsManager.h"

EpisodesListHandler::EpisodesListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

void EpisodesListHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                                  std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                                  std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    gameMonitor.episodesList(sendQueue);
}
