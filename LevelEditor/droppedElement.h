#ifndef DROPPEDELEMENT_H
#define DROPPEDELEMENT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class DroppedElement : public QWidget {
    Q_OBJECT

public:
    DroppedElement(const QString& elementType, const QPixmap& sprite, QWidget* parent = nullptr) : QWidget(parent) {
        this->elementType = elementType;
        this->sprite = sprite;
    }

    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.drawPixmap(0, 0, sprite);
    }

private:
    QString elementType;
    QPixmap sprite;
};


#endif  // DROPPEDELEMENT_H
