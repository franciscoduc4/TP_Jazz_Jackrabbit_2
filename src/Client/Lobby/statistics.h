#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMainWindow>

#include "Types/finalStats.h"
#include "Types/lobbyMessage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Statistics;
}
QT_END_NAMESPACE

class Statistics : public QMainWindow {
    Q_OBJECT

public:
    Statistics(QWidget *parent, const LobbyMessage& msg, const FinalStats& stats, bool& clientJoinedGame, const uint8_t& playerId);
    ~Statistics();
    void displayStats();

private:
    Ui::Statistics *ui;
    FinalStats stats;
    LobbyMessage msg;
    const uint8_t& playerId;
    bool& clientJoinedGame;
};


#endif  // STATISTICS_H
