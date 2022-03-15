#include "star_6.h"

star_6::star_6(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

star_6::~star_6(){

}
star_6::star_6(double xx)
{
    this->xx=xx*3;
}


QRectF star_6::boundingRect() const
{
    return QRectF (-xx,-xx,xx*2,xx*2);
}

void star_6::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly,poly2;
    poly<<QPoint(0,-1/3.0*xx*sqrt(3))<<QPoint(xx/2.0,1/6.0*xx*sqrt(3))<<QPoint(-xx/2.0,1/6.0*xx*sqrt(3));
    painter->drawPolygon(poly);

    poly2<<QPoint(0,1/3.0*xx*sqrt(3))<<QPoint(xx/2.0,-1/6.0*xx*sqrt(3))<<QPoint(-xx/2.0,-1/6.0*xx*sqrt(3));
    painter->drawPolygon(poly2);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
