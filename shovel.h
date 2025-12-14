#ifndef SHOVEL_H
#define SHOVEL_H

#include "other.h"

class shovel : public other
{
public:
    // 构造函数和析构函数
    shovel();
    ~shovel() override = default;

    // QGraphicsItem 接口实现
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    // 事件处理
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    // 功能方法
    void removePlant(const QPointF& position);

private:
    bool isDragging = false;
};

#endif // SHOVEL_H
