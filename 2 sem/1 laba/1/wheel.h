#ifndef WHEEL_H
#define WHEEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class wheel : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit wheel(QObject *parent = 0);
    ~wheel();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // WHEEL_H
