#include "samosval.h"

samosval::samosval(QObject  *parent) :
    QObject(parent), QGraphicsItem()
{

}

samosval::~samosval(){

}

QRectF samosval::boundingRect() const
{
    return QRectF (0,0,250,100);
}

void samosval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    //кузов

    //самосвал
    painter->drawLine(20,40,20,60);
    painter->drawLine(120,40,20,40);
    painter->drawLine(140,0,180,00);
    painter->drawLine(140,0,140,60);
    painter->drawLine(180,0,200,20);
    painter->drawLine(200,20,220,20);
    painter->drawLine(220,20,220,60);
    painter->drawLine(120,40,140,40);
    painter->drawLine(20,60,33,60);
    painter->drawLine(64,60,85,60);
    painter->drawLine(115,60,162,60);
    painter->drawLine(194,60,220,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
