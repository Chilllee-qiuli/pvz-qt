#ifndef SUN_H
#define SUN_H

#include "other.h"

class sun : public other
{
public:
    sun();
    sun(QPointF pos);
    ~sun() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
private:
    QMovie *movie;
    QPointF dest;
    int counter;
    int time;
    qreal speed;
    bool collected = false;
    void collectOnce();
    bool pendingDelete = false;
    void scheduleDestroy();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
};


#endif // SUN_H
