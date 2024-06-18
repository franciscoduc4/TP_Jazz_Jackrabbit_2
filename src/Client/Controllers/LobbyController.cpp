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

bool LobbyController::canStartGame() {
    return this->selected.getCurrentPlayers() == this->selected.getMaxPlayers();
}

GameInfo LobbyController::getSelectedGame() { return this->selected; }

// Outbound methods
void LobbyController::sendRequest(const LobbyMessage& msg) {
    // Si es un mensaje de CREATE_GAME o JOIN_GAME, me guardo la partida que se selecciona.
    if (msg.getLobbyCmd() == Command::CREATE_GAME || msg.getLobbyCmd() == Command::JOIN_GAME) {
        std::cout << "[Lobby Controller] Selected game updated." << std::endl;
        this->selected = GameInfo(msg.getGameId(), msg.getGameName(), msg.getMaxPlayers(), 1);
    }
    this->serializer.serializeLobbyMessage(msg);
}

void LobbyController::startGame(const LobbyMessage& msg) {
    std::unique_ptr<CommandDTO> startGameDTO = std::make_unique<StartGameDTO>(msg.getGameId());
    this->serializer.sendMsg(startGameDTO);
}

// Inbound methods
std::pair<bool, GameInfo> LobbyController::recvResponse() {
    std::unique_ptr<DTO> dto;
    try {
        dto = this->lobbyQueue->pop();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in recvResponse: " << e.what() << std::endl;
        return std::make_pair(false, this->selected);
    }
    auto* cmdDTO = dynamic_cast<CommandDTO*>(dto.get());
    switch (cmdDTO->getCommand()) {
        /**
         * Game ID: en CREATE_GAME se obtiene desde el servidor; en JOIN_GAME,  ya existe el dato.
         * Game Name: en ambos casos ya existe el dato.
         * Game Map: se tiene el ID del mapa en ambos casos, se actualiza si es necesario. Solo se
         * manda en GameInfo. Current Players: en CREATE_GAME es 1 siempre; en JOIN_GAME, se obtiene
         * desde el servidor. Max Players: se crea o se une a un juego sabiendo este dato
         */
        case Command::CREATE_GAME: {
            auto* cgDTO = dynamic_cast<CreateGameDTO*>(cmdDTO);
            this->selected.updateGameId(cgDTO->getGameId());
            break;
        }
        case Command::GAME_UPDATE: {
            auto* guDTO = dynamic_cast<GameUpdateDTO*>(cmdDTO);
            this->selected.updateCurrentPlayers(guDTO->getGameInfo().currentPlayers);
            if (this->selected.getMapName() == "") {
                this->selected.updateMapName(guDTO->getGameInfo().mapName);
            }
            break;
        }
        case Command::JOIN_GAME: {
            auto* jgDTO = dynamic_cast<JoinGameDTO*>(cmdDTO);
            this->selected.updateCurrentPlayers(jgDTO->getCurrentPlayers());
            break;
        }
        case Command::MAPS_LIST:
        case Command::GAMES_LIST:
        case Command::START_GAME:
            break;
        default:
            return std::make_pair(false, this->selected);
    }
    return std::make_pair(true, this->selected);
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
    std::unique_ptr<DTO> dto = this->lobbyQueue->pop();
    auto* gamesList = dynamic_cast<GamesListDTO*>(dto.get());
    this->games = std::move(gamesList->getGames());
    return this->games;
}
