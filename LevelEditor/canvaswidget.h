#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QDropEvent>
#include <QMouseEvent>
#include <QVector>
#include <QMimeData>

class
        DroppedElement; // Forward declaration

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

    void clearElements();

signals:
    void dropped(QDropEvent* event);

protected:
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private:
    QVector<DroppedElement*> droppedElements;
    DroppedElement* currentDraggedElement = nullptr;
    QPoint dragOffset;
};

#endif // CANVASWIDGET_H
