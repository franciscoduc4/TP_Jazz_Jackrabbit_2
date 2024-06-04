#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QMainWindow>

#include "../Monitors/QTMonitor.h"
#include "../Protocol/lobbyMessage.h"

namespace Ui {
class CharacterSelection;
}

class CharacterSelection : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit CharacterSelection(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~CharacterSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::CharacterSelection *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // CHARACTERSELECTION_H
