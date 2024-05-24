#include "characterselection.h"
#include "ui_characterselection.h"

#include "../Common/Constants/lobbyCommands.h"
#include "../Common/Constants/characterSelect.h"

CharacterSelection::CharacterSelection(QWidget *parent,SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::CharacterSelection),
    sender(sender),
    receiver(receiver),
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
        WaitingRoom* wr = new WaitingRoom(this->sender, this->receiver, this->monitor, this->msg);
        wr->show();
        this->close();
    } else if (this->msg.isJoinGame()) {
        GameList* gl = new GameList(this->sender, this->receiver, this->monitor, this->msg);
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
    if (this->msg.isJoinGame()) {
        Lobby* lobby = new Lobby(this->sender, this->receiver, this->monitor, this->msg);
        lobby->show();
        this->close();
    } else if (this->msg.isCreateGame()) {
        CreateGame* cg = new CreateGame(this->sender, this->receiver, this->monitor, this->msg);
        cg->show();
        this->close();
    }
}

