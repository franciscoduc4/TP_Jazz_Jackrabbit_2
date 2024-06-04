#include "characterselection.h"
#include "ui_characterselection.h"

#include "../Common/Constants/lobbyCommands.h"
#include "../../Common/Types/character.h"

#include "waitingroom.h"
#include "gamelist.h"

CharacterSelection::CharacterSelection(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
        QMainWindow(parent),
        ui(new Ui::CharacterSelection),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame),
        characterSelectionWidget(new CharacterSelectionWidget(this))
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->widgetCharacters);
    layout->addWidget(characterSelectionWidget);
}

CharacterSelection::~CharacterSelection()
{
    delete ui;
}

void CharacterSelection::on_btnChoose_clicked()
{
    this->msg.setCharacter(characterSelectionWidget->getCurrentCharacter());
    this->client.sendCharacterSelection(this->msg);
    if (this->msg.isCreateGame()) {
        WaitingRoom* wr = new WaitingRoom(this, this->client, this->msg, this->clientJoinedGame);
        wr->show();
        this->close();
    } else if (this->msg.isJoinGame()) {
        GameList* gl = new GameList(this, this->client, this->msg, this->clientJoinedGame);
        gl->show();
        this->close();
    } else {
        // Este caso no debería suceder.
        QMessageBox::warning(this, "Ocurrió un error inesperado.", "Error");
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

