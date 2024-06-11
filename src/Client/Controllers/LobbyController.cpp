#include "LobbyController.h"

#include "DTO/startGame.h"

LobbyController::LobbyController(Serializer& serializer, Deserializer& deserializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue) :
        serializer(serializer),
        deserializer(deserializer),
        lobbyQueue(lobbyQueue),
        selected(){}

void LobbyController::sendRequest(const LobbyMessage& msg) {
    if (msg.getLobbyCmd() != Command::GAMES_LIST) {
        this->selected = GameInfo(msg.getGameId(), msg.getGameName(), msg.getMaxPlayers(), 1);
    }
    this->serializer.serializeLobbyMessage(msg);
}

void LobbyController::startGame(const LobbyMessage& msg) {
    std::unique_ptr<DTO> startGameDTO = std::make_unique<StartGameDTO>(msg.getGameId());
    this->serializer.sendMsg(startGameDTO);
}

std::map<uint32_t, GameInfo>& LobbyController::getGamesList() {
    std::unique_ptr<DTO> dto;
    GamesListDTO* games;
    try {
        dto = this->lobbyQueue->pop();
        games = dynamic_cast<GamesListDTO*>(dto.get());
    } catch (std::exception &e) {
        return this->games;
    }

    this->games = std::move(games->getGames());

    return this->games;
}

/*
void LobbyController::waitForGameStart() {
    QMutexLocker locker(&mutex);
    while (true) {
        condition.wait(&mutex);
        std::unique_ptr<DTO> dto = deserializer.popFromQueue();
        if (dynamic_cast<StartGameDTO*>(dto.get()) != nullptr) {
            // Game has started
            break;
        }
    }
}
*/
