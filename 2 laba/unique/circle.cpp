#include "circle.h"

circle::circle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

circle::~circle(){

}


QRectF circle::boundingRect() const
{
    return QRectF (0,0,50,50);
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(0,0,50,50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
