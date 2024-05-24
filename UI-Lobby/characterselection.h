#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QMainWindow>
#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"


namespace Ui {
class CharacterSelection;
}

class CharacterSelection : public QMainWindow
{
    Q_OBJECT
    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    explicit CharacterSelection(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~CharacterSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::CharacterSelection *ui;
};

#endif // CHARACTERSELECTION_H
