#ifndef STAR_5_H
#define STAR_5_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QtMath>


class star_5 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit star_5(QObject *parent = 0);
    ~star_5();
    star_5(double);

private:
    double xx;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // STAR_5_H
