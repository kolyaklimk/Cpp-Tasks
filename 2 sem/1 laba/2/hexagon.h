#ifndef HEXAGON_H
#define HEXAGON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QtMath>


class hexagon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit hexagon(QObject *parent = 0);
    ~hexagon();
    hexagon(double);

private:
    double xx;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // HEXAGON_H
