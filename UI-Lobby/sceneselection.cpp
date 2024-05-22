#include "sceneselection.h"
#include "ui_sceneselection.h"

SceneSelection::SceneSelection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneSelection)
{
    ui->setupUi(this);
}

SceneSelection::~SceneSelection()
{
    delete ui;
}
