#include "gameStatusMonitor.h"

GameStatusMonitor::GameStatusMonitor() : isRunning(true) {}

bool GameStatusMonitor::gameIsRunning() {
    return this->isRunning;
}