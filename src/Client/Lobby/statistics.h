#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMainWindow>

#include "Types/finalStats.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Statistics;
}
QT_END_NAMESPACE

class Statistics : public QMainWindow {
    Q_OBJECT

public:
    Statistics(QWidget *parent, FinalStats stats, bool& clientJoinedGame);
    ~Statistics();
    void displayStats();

private:
    Ui::Statistics *ui;
    FinalStats stats;
    bool& clientJoinedGame;
};


#endif  // STATISTICS_H
