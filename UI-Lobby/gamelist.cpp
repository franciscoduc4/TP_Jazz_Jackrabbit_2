#include "gamelist.h"
#include "ui_gamelist.h"

GameList::GameList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameList)
{
    ui->setupUi(this);
}

GameList::~GameList()
{
    delete ui;
}
