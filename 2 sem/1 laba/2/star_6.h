#ifndef STAR_6_H
#define STAR_6_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QtMath>


class star_6 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit star_6(QObject *parent = 0);
    ~star_6();
    star_6(double);

private:
    double xx;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // STAR_6_H
