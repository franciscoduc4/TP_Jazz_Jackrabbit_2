#include "shoot.h"

ShootHandler::ShootHandler(std::unique_ptr<CommandDTO> shootCommand):
        shootCommand(std::move(shootCommand)) {}

void ShootHandler::execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = game.getCharacter(shootCommand->getPlayerId());
    character->shoot(deltaTime);
    // game.addBullet(bullet);
}