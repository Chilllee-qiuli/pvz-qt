#include "wallnut.h"

wallnut::wallnut()
{
    hp=3000;
    setMovie(":/new/prefix1/WallNut.gif");
}
void wallnut::advance(int phase)
{
    if(!phase)
        return;

    if(hp<=0)
    {
        delete this;
        return;
    }
    else if(hp<1000)
    {
        setMovie(":/new/prefix1/WallNut2.gif");
        return;
    }
    else if(hp<2000)
    {
        setMovie(":/new/prefix1/WallNut1.gif");
        return;
    }
}


QString wallnut::getInfo() const
{
    // QString s = QString("血量值：%d ,攻击值: %d ").arg(atk) .arg(hp);
        QString s = QString("血量值：%1 ,攻击值: %2 ").arg(hp) .arg(atk);
    return s;
}
