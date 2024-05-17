#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include "name_screen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Lobby;
}
QT_END_NAMESPACE

class Lobby : public QMainWindow
{
    Q_OBJECT

public:
    Lobby(QWidget *parent = nullptr);
    ~Lobby();

private slots:
    void on_play_clicked();

private:
    Ui::Lobby *ui;
    //Name_screen *n_screen;
};
#endif // LOBBY_H
