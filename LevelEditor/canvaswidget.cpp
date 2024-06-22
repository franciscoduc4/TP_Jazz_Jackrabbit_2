#include "canvaswidget.h"

#include <QPainter>

#include "SpritesManager.h"
#include "droppedElement.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent) {
    setFixedSize(1000, 1000);
    setAcceptDrops(true);
}

CanvasWidget::~CanvasWidget() {
    for (auto element : droppedElements) {
        delete element;
    }
}

void CanvasWidget::dropEvent(QDropEvent *event) {
    QPoint dropPos = event->pos();
    // Get elementType and sprite from your drag and drop data or SpritesManager
    QString elementType =  event->mimeData()->text();
    QPixmap sprite = SpritesManager::get(elementType);
    // Create the DroppedElement with all the necessary information
    DroppedElement *newElement = new DroppedElement(elementType, dropPos, sprite, this);
    newElement->show();
    droppedElements.append(newElement);
    event->acceptProposedAction();
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) override {
    for (DroppedElement* element : droppedElements) {
        if (element->geometry().contains(event->pos())) {
            currentDraggedElement = element;
            dragOffset = event->pos() - element->pos();
            break;
        }
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) override {
    if (currentDraggedElement) {
        QPoint newPos = event->pos() - dragOffset;
        currentDraggedElement->move(newPos);
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) override {
    currentDraggedElement = nullptr;
}
