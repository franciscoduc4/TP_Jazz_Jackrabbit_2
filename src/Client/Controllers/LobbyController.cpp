#include "LobbyController.h"

#include <iostream>

#include "DTO/createGame.h"
#include "DTO/joinGame.h"
#include "DTO/startGame.h"

LobbyController::LobbyController(Serializer& serializer, Deserializer& deserializer,
                                 std::shared_ptr<Queue<std::unique_ptr<DTO>>>& lobbyQueue):
        serializer(serializer),
        deserializer(deserializer),
        lobbyQueue(lobbyQueue),
        games(std::unordered_map<uint8_t, GameInfo>()),
        selected() {}

// Updates
bool LobbyController::hasGameUpdates(std::unique_ptr<DTO>& dto) {
    return this->lobbyQueue->try_pop(dto);
}

int LobbyController::processGameUpdate(std::unique_ptr<DTO>& dto) {
    auto* gameInfoDTO = dynamic_cast<GameInfo*>(dto.get());
    if (gameInfoDTO) {
        this->selected = *gameInfoDTO;
    }
    return static_cast<int>(this->selected.getCurrentPlayers());
}


// Outbound methods
void LobbyController::sendRequest(const LobbyMessage& msg) {
    // Si es un mensaje de CREATE_GAME o JOIN_GAME, me guardo la partida que se selecciona.
    if (msg.getLobbyCmd() == Command::CREATE_GAME || msg.getLobbyCmd() == Command::JOIN_GAME) {
        this->selected = GameInfo(msg.getGameId(), msg.getGameName(), msg.getMaxPlayers(), 1);
    }
    this->serializer.serializeLobbyMessage(msg);
}

void LobbyController::startGame(const LobbyMessage& msg) {
    std::unique_ptr<CommandDTO> startGameDTO = std::make_unique<StartGameDTO>(msg.getGameId());
    this->serializer.sendMsg(startGameDTO);
}

// Inbound methods
bool LobbyController::recvResponse() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in recvResponse: " << e.what() << std::endl;
        return false;
    }
    auto* cmdDTO = dynamic_cast<CommandDTO*>(dto.get());
    switch (cmdDTO->getCommand()) {
        case Command::CREATE_GAME: {
            auto* cgDTO = dynamic_cast<CreateGameDTO*>(cmdDTO);
            // this->selected = GameInfo(cgDTO->getGameId(), cgDTO->getGameName(), cgDTO->getMaxPlayers(), cgDTO->getCurrentPlayers());
            this->selected = GameInfo(cgDTO->getGameId(), cgDTO->getGameName(), cgDTO->getMaxPlayers(), 1);
            break;
        }
        case Command::JOIN_GAME: {
            auto* jgDTO = dynamic_cast<JoinGameDTO*>(cmdDTO);
            // this->selected = GameInfo(jgDTO->getGameId(), jgDTO->getGameName(), jgDTO->getMaxPlayers(), jgDTO->getCurrentPlayers());
            this->selected = GameInfo(jgDTO->getGameId(), "", 3, jgDTO->getCurrentPlayers());
            break;
        }
        case Command::MAPS_LIST:
        case Command::GAMES_LIST:
        case Command::START_GAME:
            break;
        default:
            return false;
    }
    return true;
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
    return sgDTO->getCommand() == Command::START_GAME;
}

// TODO: detonar esto - debería recibirse todo el Game.
uint8_t LobbyController::recvCreateGame() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (const std::exception& e) {
        return 0;
    }
    auto* cgDTO = dynamic_cast<CreateGameDTO*>(dto.get());
    return cgDTO->getGameId();
}

std::unordered_map<uint8_t, std::string> LobbyController::getMaps() {
    try {
        std::unique_ptr<DTO> dto = this->lobbyQueue->pop();
        auto* mapsList = dynamic_cast<MapsListDTO*>(dto.get());
        return std::move(mapsList->getMapsMap());
    } catch (const std::exception& e) {
        std::cerr << "[Lobby Controller] Exception caught in getMaps: " << e.what() << std::endl;
        return {};
    }
}

std::unordered_map<uint8_t, GameInfo>& LobbyController::getGamesList() {
    std::unique_ptr<DTO> dto;
    GamesListDTO* gamesList;
    try {
        dto = this->lobbyQueue->pop();
        gamesList = dynamic_cast<GamesListDTO*>(dto.get());
        this->games = std::move(gamesList->getGames());
    } catch (const std::exception& e) {
        std::cerr << "[Lobby Controller] Exception caught in getGamesList: " << e.what() << std::endl;
    }
    return this->games;
}
