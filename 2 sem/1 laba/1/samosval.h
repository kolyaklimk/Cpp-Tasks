#ifndef SAMOSVAL_H
#define SAMOSVAL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class samosval : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit samosval(QObject *parent = 0);
    ~samosval();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SAMOSVAL_H
