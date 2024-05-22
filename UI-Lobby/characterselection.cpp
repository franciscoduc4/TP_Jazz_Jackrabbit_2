#include "characterselection.h"
#include "ui_characterselection.h"

CharacterSelection::CharacterSelection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CharacterSelection)
{
    ui->setupUi(this);
}

CharacterSelection::~CharacterSelection()
{
    delete ui;
}
