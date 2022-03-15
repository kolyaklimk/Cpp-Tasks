#ifndef KUZOV_H
#define KUZOV_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class kuzov : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit kuzov(QObject *parent = 0);
    ~kuzov();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // KUZOV_H
