#ifndef STAR_8_H
#define STAR_8_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QtMath>


class star_8 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit star_8(QObject *parent = 0);
    ~star_8();
    star_8(double);

private:
    double xx;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // STAR_8_H
