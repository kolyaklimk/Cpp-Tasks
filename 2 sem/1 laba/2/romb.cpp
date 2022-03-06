#include "romb.h"

romb::romb(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

romb::~romb(){

}
romb::romb(double xx,double yy)
{
    this->xx=xx;
    this->yy=yy;
}


QRectF romb::boundingRect() const
{
    return QRectF (-xx,-yy,xx*2,yy*2);
}

void romb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly;
    poly<<QPoint(0,-yy/2.0)<<QPoint(xx/2.0,0)<<QPoint(0,yy/2.0)<<QPoint(-xx/2.0,0);
    painter->drawPolygon(poly);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
