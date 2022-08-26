#include "triangle.h"

triangle::triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

triangle::~triangle(){

}
triangle::triangle(double xx)
{
    this->xx=xx;
}


QRectF triangle::boundingRect() const
{
    return QRectF (-xx,-xx,xx*2,xx*2);
}

void triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly;
    poly<<QPoint(0,-1/3.0*xx*sqrt(3))<<QPoint(xx/2.0,1/6.0*xx*sqrt(3))<<QPoint(-xx/2.0,1/6.0*xx*sqrt(3));
    painter->drawPolygon(poly);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
