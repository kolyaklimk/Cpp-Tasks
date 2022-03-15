#include "line.h"

line::line(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

line::~line(){

}

line::line(int x, int y)
{
    this->x=x;
    this->y=y;
}


QRectF line::boundingRect() const
{
    return QRectF (0,0,730,380);
}

void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly;
    poly<<QPoint(500, 50);
    poly<<QPoint(x+25, y+25);
    painter->drawPolygon(poly);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
