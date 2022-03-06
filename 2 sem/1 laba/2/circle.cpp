#include "circle.h"

circle::circle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

circle::~circle(){

}

circle::circle(double radius)
{
    this->radius=radius;
}


QRectF circle::boundingRect() const
{
    return QRectF (-radius/4-2,-radius/4-2,radius/2+4,radius/2+4);
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    painter->drawEllipse(-radius/4.0,-radius/4.0,radius/2.0,radius/2.0);
    painter->drawPoint(0,0);
    //painter->translate(xc, yc);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
