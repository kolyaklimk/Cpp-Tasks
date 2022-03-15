#ifndef CIRCLE2_H
#define CIRCLE2_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>


class circle2 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit circle2(QObject *parent = 0);
    ~circle2();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIRCLE2_H
