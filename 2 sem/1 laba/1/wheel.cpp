#include "wheel.h"

wheel::wheel(QObject  *parent) :
    QObject(parent), QGraphicsItem()
{

}

wheel::~wheel(){

}

QRectF wheel::boundingRect() const
{
    return QRectF (-25,-25,50,50);
}

void wheel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    painter->drawEllipse(-20,-20,40,40);
    painter->drawEllipse(-10,-10,20,20);
    painter->drawLine(0,-10,0,-20);
    painter->drawLine(0,10,0,20);
    painter->drawLine(10,00,20,0);
    painter->drawLine(-10,00,-20,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
