#ifndef CHOMPER_H
#define CHOMPER_H

#include "plant.h"

class chomper : public plant
{
public:
    enum ChomperState {
        STATE_INITIAL,
        STATE_ATTACKING,
        STATE_CHEWING
    };

    chomper();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    QString getInfo() const override;

private:
    ChomperState currentState;
    int chewCounter;  // 用于记录嚼僵尸的时间
    const int CHEW_TIME = 300;  // 嚼僵尸的总时间，可根据实际情况调整
};

#endif // CHOMPER_H
