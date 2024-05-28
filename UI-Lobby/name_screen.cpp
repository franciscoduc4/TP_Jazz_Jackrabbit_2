#include "name_screen.h"
#include "ui_name_screen.h"

Name_screen::Name_screen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Name_screen)
{
    ui->setupUi(this);
}

Name_screen::~Name_screen()
{
    delete ui;
}
