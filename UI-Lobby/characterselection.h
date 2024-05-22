#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QMainWindow>

namespace Ui {
class CharacterSelection;
}

class CharacterSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit CharacterSelection(QWidget *parent = nullptr);
    ~CharacterSelection();

private:
    Ui::CharacterSelection *ui;
};

#endif // CHARACTERSELECTION_H
