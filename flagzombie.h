#ifndef FLAGZOMBIE_H
#define FLAGZOMBIE_H

#include "zombie.h"
#include "plant.h"

class FlagZombie : public zombie
{
public:
    FlagZombie();
    void advance(int phase) override;
    int getHp() const override;
    int getAtk() const override;
    qreal getSPD() const override;
    bool checkCollisionWithPlant() const;
    void attackPlant();
    void handleDeath();
    void moveForward();
};

#endif // FLAGZOMBIE_H
