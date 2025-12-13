#ifndef WALLNUT_H
#define WALLNUT_H

#include "plant.h"

class wallnut : public plant
{
public:
    wallnut();
    void advance(int phase) override;
    QString getInfo() const override;
};


#endif // WALLNUT_H
