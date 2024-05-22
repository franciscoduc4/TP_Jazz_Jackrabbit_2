#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaitingRoom)
{
    ui->setupUi(this);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}
