#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMainWindow>

#include "../Monitors/QTMonitor.h"
#include "../Protocol/lobbyMessage.h"

namespace Ui {
class GameList;
}

class GameList : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit GameList(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~GameList();

private slots:
    void on_btnBack_clicked();

    void on_btnJoin_clicked();

private:
    Ui::GameList *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // GAMELIST_H
