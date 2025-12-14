#ifndef BASICZOMBIE_H
#define BASICZOMBIE_H

#include "zombie.h"
#include "plant.h"

class basiczombie : public zombie
{
public:
    basiczombie();
    void advance(int phase) override;
    int getHp() const override;
    int getAtk() const override;
    qreal getSPD() const override;
    bool checkCollisionWithPlant() const;
    void attackPlant();
    void handleDeath();
    void moveForward();
};


#endif // BASICZOMBIE_H
