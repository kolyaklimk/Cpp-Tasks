#ifndef LINE_H
#define LINE_H



#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>


class line : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit line(QObject *parent = 0);
    ~line();
    line(int x, int y);
    int x;
    int y;


private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // LINE_H
