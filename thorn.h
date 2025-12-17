#ifndef THORN_H
#define THORN_H

#include "plant.h"

class thorn : public plant {
public:
    thorn();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QString getInfo() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int damageInterval;
    int damageCounter;
};

#endif // THORN_H
