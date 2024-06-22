#ifndef DROPPEDELEMENT_H
#define DROPPEDELEMENT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class DroppedElement : public QWidget {
    Q_OBJECT

public:
    DroppedElement(const QString& elementType, const QPoint& position, const QPixmap& sprite, QWidget* parent = nullptr);

    QPoint position() const;
    QString elementType() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_elementType;
    QPixmap m_sprite;
    QPoint m_position;
};

#endif  // DROPPEDELEMENT_H
