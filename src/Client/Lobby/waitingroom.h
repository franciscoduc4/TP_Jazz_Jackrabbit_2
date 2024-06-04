#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QMainWindow>

#include "../Monitors/QTMonitor.h"
#include "../Protocol/lobbyMessage.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QMainWindow
{
    Q_OBJECT
    


public:
    explicit WaitingRoom(QWidget *parent , QTMonitor& monitor, LobbyMessage& msg);
    ~WaitingRoom();

private slots:
    void on_btnBack_clicked();

private:
    Ui::WaitingRoom *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // WAITINGROOM_H
