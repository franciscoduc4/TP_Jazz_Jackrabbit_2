#ifndef DTOVALIDATOR_H
#define DTOVALIDATOR_H

#include <iostream>

#include "Types/character.h"
#include "Types/command.h"
#include "Types/direction.h"
#include "Types/dto.h"
#include "Types/elements.h"
#include "Types/enemy.h"
#include "Types/entity.h"
#include "Types/gameMode.h"
#include "Types/item.h"
#include "Types/lobbyState.h"
#include "Types/weapon.h"
class DTOValidator {
public:
    static bool validateCharacterType(const char& type) {
        return type >= static_cast<char>(CharacterType::JAZZ) &&
               type < static_cast<char>(CharacterType::INVALID);
    }
    static bool validateCommandType(const char& type) {
        return type >= static_cast<char>(Command::IDLE) &&
               type < static_cast<char>(Command::INVALID);
    }
    static bool validateDirectionType(const char& type) {
        return type >= static_cast<char>(Direction::UP) &&
               type < static_cast<char>(Direction::RIGHT);
    }
    static bool validateDTOType(const char& type) {
        std::cout << (type >= static_cast<char>(DTOType::COMMAND_DTO)) << std::endl;
        std::cout << (type < static_cast<char>(DTOType::GAME_DTO)) << std::endl;
        return type >= static_cast<char>(DTOType::COMMAND_DTO) &&
               type < static_cast<char>(DTOType::GAME_DTO);
    }
    static bool validateElementType(const char& type) {
        return type >= static_cast<char>(ElementType::PLAYER) &&
               type < static_cast<char>(ElementType::NONE);
    }
    static bool validateEnemyType(const char& type) {
        return type >= static_cast<char>(EnemyType::WALKING_ENEMY) &&
               type < static_cast<char>(EnemyType::JUMPING_ENEMY);
    }
    static bool validateCharacterStateEntityType(const char& type) {
        return type >= static_cast<char>(CharacterStateEntity::IDLE) &&
               type < static_cast<char>(CharacterStateEntity::RESPAWNING);
    }
    static bool validateEnemyStateEntityType(const char& type) {
        return type >= static_cast<char>(EnemyStateEntity::ENEMY_IDLE) &&
               type < static_cast<char>(EnemyStateEntity::ENEMY_RESPAWNING);
    }
    static bool validateEpisodeType(const char& type) {
        //return type >= static_cast<char>(Episode::INVALID) && type < static_cast<char>(Episode::BEACH);
    }
    static bool validateGameMode(const char& type) {
        return type >= static_cast<char>(GameMode::SINGLE_PLAYER) &&
               type < static_cast<char>(GameMode::PARTY_MODE);
    }
    static bool validateItemType(const char& type) {
        return type >= static_cast<char>(ItemType::GEM) &&
               type < static_cast<char>(ItemType::SILVER_COIN);
    }
    static bool validateLobbyState(const char& type) {
        return type >= static_cast<char>(LobbyState::GAME_CREATED) &&
               type < static_cast<char>(LobbyState::GAMES_LIST);
    }
    static bool validateWeaponType(const char& type) {
        return type >= static_cast<char>(WeaponType::BLASTER) &&
               type < static_cast<char>(WeaponType::FREEZER);
    }
};

#endif  // DTOVALIDATOR_H
