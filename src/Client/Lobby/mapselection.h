#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QButtonGroup>
#include <QDialog>
#include <QGraphicsBlurEffect>
#include <QRadioButton>
#include <QFile>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../Controllers/LobbyController.h"
#include "Types/lobbyMessage.h"

namespace Ui {
class MapSelection;
}

class MapSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelection(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~MapSelection();

private slots:
    void on_btnChoose_clicked();
    void on_btnBack_clicked();

private:
    Ui::MapSelection *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    QButtonGroup* buttonGroup;
};

#endif // MAPSELECTION_H
