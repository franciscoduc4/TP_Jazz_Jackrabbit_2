#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QMessageBox>

#include "../client.h"
#include "../Protocol/lobbyMessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    Welcome(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~Welcome();

private slots:
    void on_btnIngresar_clicked();

private:
    Ui::Welcome *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // WELCOME_H
