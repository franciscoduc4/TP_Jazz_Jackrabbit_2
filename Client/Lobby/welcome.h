#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QMessageBox>

#include "../Client/QTMonitor.h"
#include "../Client/lobbyMessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    Welcome(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~Welcome();

private slots:
    void on_btnIngresar_clicked();

private:
    Ui::Welcome *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // WELCOME_H
