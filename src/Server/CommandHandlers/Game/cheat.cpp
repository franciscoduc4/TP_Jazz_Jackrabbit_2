#include "cheat.h"

CheatHandler::CheatHandler(std::unique_ptr<CommandDTO> command) : command(std::move(command)) {}

/**
 * @brief Ejecuta un comando de trampa en el juego, como terminar el juego o reiniciar puntajes.
 * 
 * @param gameMap Mapa del juego donde se aplican los efectos de la trampa.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void CheatHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    auto* cheatCommand = dynamic_cast<CheatDTO*>(command.get());
    switch (cheatCommand->getCheat()) {
        case Cheat::END_GAME: {
            keepRunning.store(false);
            break;
        }
        case Cheat::RESET_SCORES: {
            gameMap.resetScores();
            break;
        }
    }
}
