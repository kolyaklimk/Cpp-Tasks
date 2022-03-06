#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>


class circle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit circle(QObject *parent = 0);
    ~circle();
    circle(double);

private:
    double radius;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIRCLE_H
