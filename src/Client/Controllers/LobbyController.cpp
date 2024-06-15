#include "LobbyController.h"

#include <iostream>

#include "DTO/createGame.h"
#include "DTO/startGame.h"

LobbyController::LobbyController(Serializer& serializer, Deserializer& deserializer,
                                 std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue):
        serializer(serializer),
        deserializer(deserializer),
        lobbyQueue(lobbyQueue),
        games(std::unordered_map<uint8_t, GameInfo>()),
        selected() {}

void LobbyController::sendRequest(const LobbyMessage& msg) {
    // Si es un mensaje de CREATE_GAME o JOIN_GAME, me guardo la partida que se selecciona.
    if (msg.getLobbyCmd() == Command::CREATE_GAME || msg.getLobbyCmd() == Command::JOIN_GAME) {
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
        std::cout << "[LOBBY CONTROLLER] Received start game DTO." << std::endl;
        return sgDTO->getCommand() == Command::START_GAME;
    } else {
        std::cerr << "Failed to cast to StartGameDTO in recvStartGame." << std::endl;
        return false;
    }
}

std::unordered_map<uint8_t, std::string> LobbyController::getMaps() {
    std::cout << "[Lobby Controller] Getting maps..." << std::endl;
    try {
        std::unique_ptr<DTO> dto = this->lobbyQueue->pop();
        auto* mapsList = dynamic_cast<MapsListDTO*>(dto.get());
        std::cout << "[Lobby Controller] Returning maps..." << std::endl;
        return std::move(mapsList->getMapsMap());
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in getMaps: " << e.what() << std::endl;
    }
    std::cout << "[Lobby Controller] Returning empty map..." << std::endl;
    return {};
}

std::unordered_map<uint8_t, GameInfo>& LobbyController::getGamesList() {
    std::unique_ptr<DTO> dto;
    GamesListDTO* gamesList;
    try {
        dto = this->lobbyQueue->pop();
        gamesList = dynamic_cast<GamesListDTO*>(dto.get());
        this->games = std::move(gamesList->getGames());
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in getGamesList: " << e.what() << std::endl;
    }
    return this->games;
}
