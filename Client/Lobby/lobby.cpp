#include "lobby.h"
#include "./ui_lobby.h"
#include "name_screen.h"

#include <QString>
#include <QPixmap>

Lobby::Lobby(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lobby)
{
    ui->setupUi(this);
    /*
    QString url = R"(TP_Jazz_Jackrabbit_2\assets\Miscellaneous\Miscellaneous.png)";
    QPixmap img(url);
    img = img.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->label->setPixmap(img);
    ui->label->setScaledContents(true);
    */
    ui->labelName->setVisible(false);
    ui->userName->setVisible(false);
    ui->continuar->setVisible(false);


}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_play_clicked()
{
    /*
    esto queda mal

    n_screen = new Name_screen();
    n_screen->setModal(true);
    n_screen->show();
    destroy();
    this->close();
    */

    //no se si se puede hacer esto
    delete ui->play;
    ui->labelName->setVisible(true);
    ui->userName->setVisible(true);
    ui->continuar->setVisible(true);
    //ui->centralwidget->setStyleSheet("border-image: url(/carga.png)");
    ui->centralwidget->setStyleSheet("border-image: url(TP_Jazz_Jackrabbit_2\assets\Miscellaneous\carga.png)");


    //verificar si esta bien el nombre de usuario
}


