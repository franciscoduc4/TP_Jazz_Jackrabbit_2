#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

#include "../Common/socket.h"
#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QMainWindow
{
    Q_OBJECT

    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    Welcome(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~Welcome();

private slots:
    void on_btnIngresar_clicked();

private:
    Ui::Welcome *ui;
};
#endif // WELCOME_H
