#ifndef ROMB_H
#define ROMB_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>


class romb : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit romb(QObject *parent = 0);
    ~romb();
    romb(double,double);

private:
    double xx,yy;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ROMB_H
