#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>

#include "../Common/socket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Lobby; }
QT_END_NAMESPACE

class Lobby : public QMainWindow
{
    Q_OBJECT

    Socket& skt;

public:
    Lobby(QWidget *parent = nullptr, Socket& skt);
    ~Lobby();

private slots:
    void on_btnIngresar_clicked();

private:
    Ui::Lobby *ui;
};
#endif // LOBBY_H
