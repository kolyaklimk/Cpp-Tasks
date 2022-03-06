#include "star_5.h"

star_5::star_5(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

star_5::~star_5(){

}
star_5::star_5(double xx)
{
    this->xx=xx*1.666;
}

QRectF star_5::boundingRect() const
{
    return QRectF (-xx,-xx,xx*2,xx*2);
}

void star_5::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly;
    float angle = 3.14 / 180.0 * (360 / 5);
    float x1=-xx/2,x2=xx/2;
    float y1=-xx/4*2.7,y2=-xx/4*2.7;
    poly<<QPoint(x1, y1);
    for (int i = 0; i < 5 - 1; i++)
    {
        float nextX = (float)((x2 - x1) * cos(angle) + (y2 - y1) * -sin(angle)) + x2;
        float nextY = (float)((x2 - x1) * sin(angle) + (y2 - y1) * cos(angle)) + y2;
        poly<<QPoint(nextX, nextY);
        poly<<QPoint(x1, y1);
        x1 = x2; y1 = y2; x2 = nextX; y2 = nextY;
    }
    painter->drawPolygon(poly);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
