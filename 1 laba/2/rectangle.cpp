#include "rectangle.h"

rectangle::rectangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

rectangle::~rectangle(){

}
rectangle::rectangle(double xx,double yy)
{
    this->xx=xx;
    this->yy=yy;
}


QRectF rectangle::boundingRect() const
{
    return QRectF (-xx,-yy,xx*2,yy*2);
}

void rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    painter->drawRect(-xx/2.0,-yy/2.0,xx,yy);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
