#include "LobbyController.h"
#include "DTO/startGame.h"
#include "DTO/createGame.h"
#include <iostream>

LobbyController::LobbyController(Serializer& serializer, 
    Deserializer& deserializer, 
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue) :
        serializer(serializer),
        deserializer(deserializer),
        lobbyQueue(lobbyQueue),
        games(std::map<uint32_t, GameInfo>()),
        selected() {}

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
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in recvResponse: " << e.what() << std::endl;
        return false;
    }
    auto* cgDTO = dynamic_cast<CreateGameDTO*>(dto.get());
    if (cgDTO) {
        return cgDTO->getCommand() == Command::CREATE_GAME;
    } else {
        std::cerr << "Failed to cast to CreateGameDTO in recvResponse." << std::endl;
        return false;
    }
}

void LobbyController::startGame(const LobbyMessage& msg) {
    std::unique_ptr<CommandDTO> startGameDTO = std::make_unique<StartGameDTO>(msg.getGameId());
    this->serializer.sendMsg(startGameDTO);
}

bool LobbyController::recvStartGame() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in recvStartGame: " << e.what() << std::endl;
        return false;
    }
    auto* sgDTO = dynamic_cast<StartGameDTO*>(dto.get());
    if (sgDTO) {
        return sgDTO->getCommand() == Command::START_GAME;
    } else {
        std::cerr << "Failed to cast to StartGameDTO in recvStartGame." << std::endl;
        return false;
    }
}

std::map<uint32_t, GameInfo>& LobbyController::getGamesList() {
    std::unique_ptr<DTO> dto;
    GamesListDTO* gamesList;
    try {
        dto = this->lobbyQueue->pop();
        gamesList = dynamic_cast<GamesListDTO*>(dto.get());
        if (gamesList) {
            this->games = std::move(gamesList->getGames());
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in getGamesList: " << e.what() << std::endl;
    }
    return this->games;
}
