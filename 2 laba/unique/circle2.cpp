#include "circle2.h"

circle2::circle2(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

circle2::~circle2(){

}


QRectF circle2::boundingRect() const
{
    return QRectF (0,0,100,100);
}

void circle2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::blue));
    painter->drawEllipse(0,0,80,80);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
