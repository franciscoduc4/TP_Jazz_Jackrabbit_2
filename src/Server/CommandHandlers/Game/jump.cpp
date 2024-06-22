#include "jump.h"

JumpHandler::JumpHandler(std::unique_ptr<CommandDTO> jumpCommand):
        moveCommand(std::move(jumpCommand)) {}

void JumpHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "EMPEZO LA EJECUCION DEL SALTO\n";
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    character->jump(deltaTime);
    std::cout << "TERMINO DE EJECUTARSE EL SALTO\n";
}