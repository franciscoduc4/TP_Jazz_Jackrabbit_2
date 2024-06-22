#include "canvaswidget.h"

#include <QPainter>
#include <QDebug>

#include "SpritesManager.h"
#include "droppedElement.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent) {
    setFixedSize(1000, 1000);
    setAcceptDrops(true);
    qDebug() << "CanvasWidget created";
}

CanvasWidget::~CanvasWidget() {
    for (auto element : droppedElements) {
        delete element;
    }
}

void CanvasWidget::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << "Drag enter event";
    event->acceptProposedAction();
}

void CanvasWidget::dragMoveEvent(QDragMoveEvent *event) {
    qDebug() << "Drag move event";
    event->acceptProposedAction();
}

void CanvasWidget::dropEvent(QDropEvent *event) {
    qDebug() << "Drop event";
    const QMimeData *mimeData = event->mimeData();
    qDebug() << "Format --> " << mimeData->formats();
    if (mimeData->hasFormat("application/x-dnditemdata")) {
        qDebug() << "Dropped";
        QByteArray itemData = mimeData->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString elementType;
        QPixmap sprite;

        dataStream >> elementType >> sprite;

        QPoint position = event->pos();

        auto *newElement = new DroppedElement(elementType, position, sprite, this);
        newElement->show();
        droppedElements.append(newElement);
        event->acceptProposedAction();

        emit dropped(event);
    }
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    for (DroppedElement* element : droppedElements) {
        painter.drawPixmap(element->pos(), element->getSprite());
    }
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    for (DroppedElement* element : droppedElements) {
        if (element->geometry().contains(event->pos())) {
            currentDraggedElement = element;
            dragOffset = event->pos() - element->pos();
            break;
        }
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    if (currentDraggedElement) {
        QPoint newPos = event->pos() - dragOffset;
        currentDraggedElement->move(newPos);
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    currentDraggedElement = nullptr;
}
