#ifndef SCENESELECTION_H
#define SCENESELECTION_H

#include <QMainWindow>

#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class SceneSelection;
}

class SceneSelection : public QMainWindow
{
    Q_OBJECT

    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    explicit SceneSelection(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~SceneSelection();

private slots:
    void on_btnChoose_clicked();

private:
    Ui::SceneSelection *ui;
};

#endif // SCENESELECTION_H
