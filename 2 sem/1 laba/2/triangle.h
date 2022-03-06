#ifndef TRIANGLE_H
#define TRIANGLE_H



#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit triangle(QObject *parent = 0);
    ~triangle();
    triangle(double);

private:
double xx;


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TRIANGLE_H
