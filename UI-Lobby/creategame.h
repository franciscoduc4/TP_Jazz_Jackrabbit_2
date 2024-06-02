#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QMainWindow>
#include "../Client/QTMonitor.h"
#include "../Client/lobbyMessage.h"
#include <QMessageBox>
#include <QObject>

namespace Ui {
class CreateGame;
}

class CreateGame : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit CreateGame(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~CreateGame();

private slots:
    void on_btnCreate_clicked();

    void on_btnBack_clicked();

private:
    Ui::CreateGame *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // CREATEGAME_H
