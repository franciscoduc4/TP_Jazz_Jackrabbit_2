#include "dropwidget.h"

DropWidget::DropWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
}

void DropWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void DropWidget::dropEvent(QDropEvent *event) {
    emit dropped(event);
}

