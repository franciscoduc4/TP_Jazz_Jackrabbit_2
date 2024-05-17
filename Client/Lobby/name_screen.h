#ifndef NAME_SCREEN_H
#define NAME_SCREEN_H

#include <QDialog>

namespace Ui {
class Name_screen;
}

class Name_screen : public QDialog
{
    Q_OBJECT

public:
    explicit Name_screen(QWidget *parent = nullptr);
    ~Name_screen();

private:
    Ui::Name_screen *ui;
};

#endif // NAME_SCREEN_H
