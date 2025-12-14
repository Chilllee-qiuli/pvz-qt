#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include "sun.h"

class sunflower : public plant
{
public:
    sunflower();
    void advance(int phase) override;
    QString getInfo() const override;
};


#endif // SUNFLOWER_H
