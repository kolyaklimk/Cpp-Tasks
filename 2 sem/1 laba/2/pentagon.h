#ifndef PENTAGON_H
#define PENTAGON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QtMath>


class pentagon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit pentagon(QObject *parent = 0);
    ~pentagon();
    pentagon(double);

private:
    double xx;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // PENTAGON_H
