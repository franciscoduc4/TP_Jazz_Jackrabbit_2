#include "deserializer.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "DTO/cheat.h"
#include "protocol.h"

/*
 * Constructor de Deserializer.
 * Inicializa el protocolo con el socket, keepPlaying y inGame.
 */
Deserializer::Deserializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame):
        protocol(std::make_shared<Protocol>(socket, keepPlaying, inGame)) {}

/*
 * Obtiene un comando deserializado basado en el ID del jugador.
 * Lee el tipo de comando del socket y llama al método de deserialización correspondiente.
 */
std::unique_ptr<CommandDTO> Deserializer::getCommand(uint8_t& playerId) {
    try {
        char cmd = 0;
        if (!protocol->receiveChar(cmd)) {
            return nullptr;
        }
        std::cout << "[SERVER DESERIALIZER] Command received: " << (int)cmd << std::endl;

        auto command = static_cast<Command>(cmd);
        switch (command) {
            case Command::CREATE_GAME:
                return deserializeCreateGame(playerId);
            case Command::MAPS_LIST:
                return deserializeMapsList(playerId);
            case Command::JOIN_GAME:
                return deserializeJoinGame(playerId);
            case Command::GAMES_LIST:
                return deserializeGamesList(playerId);
            case Command::START_GAME:
                return deserializeStart(playerId);
            case Command::IDLE:
                return deserializeIdle(playerId);
            case Command::MOVE:
                return deserializeMove(playerId);
            case Command::SWITCH_WEAPON:
                return deserializeSwitchWeapon(playerId);
            case Command::SHOOT:
                return deserializeShooting(playerId);
            case Command::SPRINT:
                return deserializeSprint(playerId);
            case Command::CHEAT:
                return deserializeCheat();
            case Command::SPECIAL_ATTACK:
                return deserializeSpecialAttack(playerId);
            default:
                std::cerr << "[SERVER DESERIALIZER] Unknown command received: " << (int)cmd << std::endl;
                return nullptr;
        }
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in getCommand: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de creación de juego.
 * Lee los datos necesarios del socket y crea un CreateGameDTO.
 */
std::unique_ptr<CreateGameDTO> Deserializer::deserializeCreateGame(uint8_t& playerId) {
    try {
        uint8_t mapId;
        protocol->receiveUInt8(mapId);

        uint8_t maxPlayers;
        protocol->receiveUInt8(maxPlayers);

        char characterTypeChar;
        protocol->receiveChar(characterTypeChar);
        auto characterType = static_cast<CharacterType>(characterTypeChar);

        uint8_t lengthName;
        protocol->receiveUInt8(lengthName);
        std::vector<char> nameBuffer(lengthName);
        protocol->receiveVectorChar(nameBuffer);
        std::string gameName(nameBuffer.begin(), nameBuffer.end());

        return std::make_unique<CreateGameDTO>(playerId, mapId, maxPlayers, characterType, gameName);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeCreateGame: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de unión a juego.
 * Lee los datos necesarios del socket y crea un JoinGameDTO.
 */
std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(uint8_t& playerId) {
    try {
        uint8_t gameId;
        if (!protocol->receiveUInt8(gameId))
            return nullptr;
        char characterTypeChar;
        if (!protocol->receiveChar(characterTypeChar))
            return nullptr;
        auto characterType = static_cast<CharacterType>(characterTypeChar);
        return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeJoinGame: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de lista de juegos.
 * Crea un GamesListDTO.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(uint8_t& playerId) {
    try {
        return std::make_unique<GamesListDTO>();
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeGamesList: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de estado inactivo.
 * Crea un GameCommandDTO con el comando IDLE.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeIdle(uint8_t& playerId) {
    try {
        return std::make_unique<GameCommandDTO>(playerId, Direction::UP, Command::IDLE);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeIdle: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de movimiento.
 * Lee la dirección del socket y crea un GameCommandDTO con el comando MOVE.
 */
std::unique_ptr<GameCommandDTO> Deserializer::deserializeMove(uint8_t& playerId) {
    try {
        char directionChar;
        if (!protocol->receiveChar(directionChar))
            return nullptr;
        Direction direction = static_cast<Direction>(directionChar);
        return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeMove: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de inicio de juego.
 * Lee el ID del juego del socket y crea un StartGameDTO.
 */
std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(uint8_t& playerId) {
    try {
        uint8_t gameId;
        if (!protocol->receiveUInt8(gameId))
            return nullptr;
        return std::make_unique<StartGameDTO>(playerId, gameId);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeStart: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de disparo.
 * Crea un CommandDTO con el comando SHOOT.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(uint8_t& playerId) {
    try {
        return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeShooting: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de cambio de arma.
 * Lee el tipo de arma del socket y crea un SwitchWeaponDTO.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(uint8_t& playerId) {
    try {
        char weaponTypeChar;
        if (!protocol->receiveChar(weaponTypeChar))
            return nullptr;
        auto weaponType = static_cast<WeaponType>(weaponTypeChar);
        return std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeSwitchWeapon: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de sprint.
 * Crea un GameCommandDTO con el comando SPRINT.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeSprint(uint8_t& playerId) {
    try {
        return std::make_unique<GameCommandDTO>(playerId, Command::SPRINT);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeSprint: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de lista de mapas.
 * Crea un MapsListDTO.
 */
std::unique_ptr<MapsListDTO> Deserializer::deserializeMapsList(uint8_t& playerId) {
    try {
        return std::make_unique<MapsListDTO>();
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeMapsList: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de trampa.
 * Lee el tipo de trampa del socket y crea un CheatDTO.
 */
std::unique_ptr<CommandDTO> Deserializer::deserializeCheat() {
    try {
        char cheatChar;
        if (!protocol->receiveChar(cheatChar))
            return nullptr;
        auto cheat = static_cast<Cheat>(cheatChar);
        return std::make_unique<CheatDTO>(cheat);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeCheat: " << e.what() << std::endl;
        return nullptr;
    }
}

/*
 * Deserializa un comando de ataque especial.
 * Crea un GameCommandDTO con el comando SPECIAL_ATTACK.
 */

std::unique_ptr<CommandDTO> Deserializer::deserializeSpecialAttack(uint8_t& playerId) {
    try {
        char characterTypeChar;
        if (!protocol->receiveChar(characterTypeChar))
            return nullptr;
        auto characterType = static_cast<CharacterType>(characterTypeChar);
        return std::make_unique<SpecialAttackDTO>(playerId, characterType);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER DESERIALIZER] Error in deserializeSwitchWeapon: " << e.what() << std::endl;
        return nullptr;
    }

}
