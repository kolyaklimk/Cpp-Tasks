#include "kuzov.h"

kuzov::kuzov(QObject  *parent) :
    QObject(parent), QGraphicsItem()
{

}

kuzov::~kuzov(){

}

QRectF kuzov::boundingRect() const
{
    return QRectF (0,0,130,50);
}

void kuzov::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    //кузов
    painter->drawLine(20,0,120,0);
    painter->drawLine(120,0,120,40);
    painter->drawLine(120,40,20,40);
    painter->drawLine(20,40,20,0);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
