#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>+

#include "../Common/socket.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
    Q_OBJECT
    const QString& playerName;
    Socket& skt;

public:
    explicit Lobby(QWidget *parent = nullptr, const QString& playerName, Socket& skt);
    ~Lobby();

private slots:
    void on_btnCreateGame_clicked();

private:
    Ui::Lobby *ui;
};

#endif // LOBBY_H
