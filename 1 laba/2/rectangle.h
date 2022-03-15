#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class rectangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit rectangle(QObject *parent = 0);
    ~rectangle();
    rectangle(double,double);

private:
double xx,yy;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // RECTANGLE_H
