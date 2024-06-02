#ifndef GAMESTATUSMONITOR_H
#define GAMESTATUSMONITOR_H

class GameStatusMonitor {
 private:
    bool isRunning;
 public:
    GameStatusMonitor();
    bool gameIsRunning();
};

#endif  // GAMESTATUSMONITOR_H
