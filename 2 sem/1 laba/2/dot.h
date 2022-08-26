#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>


class dot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit dot(QObject *parent = 0);
    ~dot();
    dot(int,int);

private:
    int x,y;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DOT_H
