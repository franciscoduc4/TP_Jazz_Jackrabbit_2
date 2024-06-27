#include "mapsListHandler.h"

#include <map>
#include <string>
#include <utility>

#include "../../../Common/maps/mapsManager.h"

/**
 * Constructor para el manejador del comando MapsList.
 *
 * @param command Puntero único a un CommandDTO que contiene los detalles del comando.
 */
MapsListHandler::MapsListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

/**
 * Ejecuta el comando MapsList, solicitando la lista de mapas disponibles al monitor del juego.
 *
 * @param gameMonitor Referencia al monitor del juego para manejar el estado del juego.
 * @param inGame Estado atómico que indica si el juego está en curso.
 * @param sendQueue Cola de envío compartida para mandar datos.
 */
void MapsListHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                              const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    gameMonitor.mapsList(sendQueue);
}
