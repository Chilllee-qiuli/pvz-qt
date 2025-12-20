#ifndef MAP_H
#define MAP_H

#include "other.h"
#include "plant.h"
#include "shop.h"
#include "shovel.h"
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
class Map : public other
{
public:
    Map();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event)override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override;
    void dropEvent(QGraphicsSceneDragDropEvent *event)override;
private:
    bool dragover;
    bool snapToGridFromScenePos(const QPointF& scenePos, QPointF& snappedScenePos) const;
    shop* findShop() const;
    shovel* findShovel() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif // MAP_H
