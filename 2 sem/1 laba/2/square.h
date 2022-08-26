#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class square : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit square(QObject *parent = 0);
    ~square();
    square(double);

private:
double xx;


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // SQUARE_H
