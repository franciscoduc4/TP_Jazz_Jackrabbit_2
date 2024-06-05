#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QMainWindow>

#include "../client.h"
#include "../Protocol/Types/lobbyMessage.h"
#include "./SelectWidgets/characterselectionwidget.h"

namespace Ui {
class CharacterSelection;
}

class CharacterSelection : public QMainWindow
{
    Q_OBJECT
    

public:
    explicit CharacterSelection(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~CharacterSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::CharacterSelection *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    CharacterSelectionWidget* characterSelectionWidget;
};

#endif // CHARACTERSELECTION_H
