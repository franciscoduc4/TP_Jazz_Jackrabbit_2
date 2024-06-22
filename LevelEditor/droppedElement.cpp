#include "droppedElement.h"
#include <QPainter>
#include <utility>

DroppedElement::DroppedElement(QString  elementType, const QPoint& position, const QPixmap& sprite, QWidget* parent)
        : QWidget(parent), m_elementType(std::move(elementType)), m_position(position), m_sprite(sprite)
{
    // Set the position and size of the widget
    setGeometry(m_position.x(), m_position.y(), m_sprite.width(), m_sprite.height());
}

void DroppedElement::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_sprite);
}

QPoint DroppedElement::position() const {
    return m_position;
}

QString DroppedElement::elementType() const {
    return m_elementType;
}

QPixmap DroppedElement::getSprite() const {
    return m_sprite;
}