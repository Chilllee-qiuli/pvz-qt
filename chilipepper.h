#ifndef CHILIPEPPER_H
#define CHILIPEPPER_H

#include "plant.h"
class chilipepper: public plant
{
public:
    chilipepper();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QString getInfo() const override;
};


#endif // CHILIPEPPER_H
