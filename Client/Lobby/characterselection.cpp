#include "characterselection.h"
#include "ui_characterselection.h"

#include "../Common/Constants/lobbyCommands.h"
#include "../Common/Constants/characterSelect.h"

#include "waitingroom.h"
#include "gamelist.h"

CharacterSelection::CharacterSelection(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::CharacterSelection),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

CharacterSelection::~CharacterSelection()
{
    delete ui;
}

void CharacterSelection::on_btnChoose_clicked()
{
    // this->msg.setCharacter(CharacterSelection::);
    if (this->msg.isCreateGame()) {
        WaitingRoom* wr = new WaitingRoom(this, this->monitor, this->msg);
        wr->show();
        this->close();
    } else if (this->msg.isJoinGame()) {
        GameList* gl = new GameList(this, this->monitor, this->msg);
        gl->show();
        this->close();
    } else {
        // Este caso no debería suceder.
        QMessageBox::warning(this, "Ocurrió un error inesperado.");
        return;
    }
}


void CharacterSelection::on_btnBack_clicked()
{
    this->msg.setCharacter(CharacterSelect::INVALID);
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

