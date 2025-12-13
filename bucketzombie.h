#ifndef BUCKETZOMBIE_H
#define BUCKETZOMBIE_H

#include "zombie.h"
#include "plant.h"

class BucketZombie : public zombie
{
public:
    BucketZombie();
    void advance(int phase) override;
    int getHp() const override;
    int getAtk() const override;
    qreal getSPD() const override;
};



#endif // BUCKETZOMBIE_H
