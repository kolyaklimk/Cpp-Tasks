#ifndef CUSTOM_H
#define CUSTOM_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class custom : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit custom(QObject *parent = 0);
    ~custom();

private:
    QPointF previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};
#endif // CUSTOM_H
