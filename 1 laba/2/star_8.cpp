#include "star_8.h"

star_8::star_8(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

star_8::~star_8(){

}
star_8::star_8(double xx)
{
    this->xx=xx/2/sin(3.14/8);
}


QRectF star_8::boundingRect() const
{
    return QRectF (-xx*2,-xx*2,xx*4,xx*4);
}

void star_8::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    double sinn=0.70710678118654752440084436210485;
    painter->drawLine(0,-xx,xx*sinn,xx*sinn);
    painter->drawLine(xx*sinn,xx*sinn,-xx,0);
    painter->drawLine(-xx,0,xx*sinn,-xx*sinn);
    painter->drawLine(xx*sinn,-xx*sinn,0,xx);
    painter->drawLine(0,xx,-xx*sinn,-xx*sinn);
    painter->drawLine(-xx*sinn,-xx*sinn,xx,0);
    painter->drawLine(xx,0,-xx*sinn,xx*sinn);
    painter->drawLine(-xx*sinn,xx*sinn,0,-xx);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
