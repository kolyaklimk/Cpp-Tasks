#include "square.h"

square::square(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

square::~square(){

}
square::square(double xx)
{
    this->xx=xx;
}


QRectF square::boundingRect() const
{
    return QRectF (-xx,-xx,xx*2,xx*2);
}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    painter->drawRect(-xx/2.0,-xx/2.0,xx,xx);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
