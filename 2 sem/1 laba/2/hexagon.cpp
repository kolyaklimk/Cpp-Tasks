#include "hexagon.h"

hexagon::hexagon(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

hexagon::~hexagon(){

}
hexagon::hexagon(double xx)
{
    this->xx=xx;
}


QRectF hexagon::boundingRect() const
{
    return QRectF (-xx,-xx,xx*2,xx*2);
}

void hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black,3));
    QPolygon poly;
    float angle = 3.14 / 180.0 * (360 / 6);
    float x1=-xx/2,x2=xx/2;
    float y1=-xx/4*3.5,y2=-xx/4*3.5;
    poly<<QPoint(x1, y1);
    for (int i = 0; i < 6 - 1; i++)
    {
        float nextX = (float)((x2 - x1) * cos(angle) + (y2 - y1) * -sin(angle)) + x2;
        float nextY = (float)((x2 - x1) * sin(angle) + (y2 - y1) * cos(angle)) + y2;
        poly<<QPoint(x2, y2);
        x1 = x2; y1 = y2; x2 = nextX; y2 = nextY;
    }
    painter->drawPolygon(poly);
    painter->drawPoint(0,0);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
