#include "LobbyController.h"

#include "DTO/startGame.h"
#include "DTO/createGame.h"

LobbyController::LobbyController(Serializer& serializer, 
    Deserializer& deserializer, 
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue) :
        serializer(serializer),
        deserializer(deserializer),
        lobbyQueue(lobbyQueue),
        games(std::map<uint32_t, GameInfo>()),
        selected(){}

void LobbyController::sendRequest(const LobbyMessage& msg) {
    if (msg.getLobbyCmd() != Command::GAMES_LIST) {
        this->selected = GameInfo(msg.getGameId(), msg.getGameName(), msg.getMaxPlayers(), 1);
    }
    this->serializer.serializeLobbyMessage(msg);
}

bool LobbyController::recvResponse() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (std::exception &e) {
        return false;
    }
    auto* cgDTO = dynamic_cast<CreateGameDTO*>(dto.get());
    return cgDTO->getCommand() == Command::CREATE_GAME;
}

void LobbyController::startGame(const LobbyMessage& msg) {
    std::unique_ptr<DTO> startGameDTO = std::make_unique<StartGameDTO>(msg.getGameId());
    this->serializer.sendMsg(startGameDTO);
}

bool LobbyController::recvStartGame() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (std::exception &e) {
        return false;
    }
    auto* sgDTO = dynamic_cast<StartGameDTO*>(dto.get());
    return sgDTO->getCommand() == Command::START_GAME;
}

std::map<uint32_t, GameInfo>& LobbyController::getGamesList() {
    std::unique_ptr<DTO> dto;
    GamesListDTO* gamesList;
    try {
        dto = this->lobbyQueue->pop();
        gamesList = dynamic_cast<GamesListDTO*>(dto.get());
    } catch (std::exception &e) {
        return this->games;
    }

    this->games = std::move(gamesList->getGames());

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
