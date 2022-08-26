#include "dot.h"

dot::dot(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

dot::~dot(){

}

dot::dot(int x,int y)
{
    this->x=x;
    this->y=y;
}


QRectF dot::boundingRect() const
{
    return QRectF (-2,-2,4,4);
}

void dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red,5));
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
