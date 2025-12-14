#ifndef SCREENZOMBIE_H
#define SCREENZOMBIE_H

#include "zombie.h"
#include "plant.h"

class ScreenZombie : public zombie
{
public:
    ScreenZombie();
    void advance(int phase) override;
    int getHp() const override;
    int getAtk() const override;
    qreal getSPD() const override;
};


#endif // SCREENZOMBIE_H
