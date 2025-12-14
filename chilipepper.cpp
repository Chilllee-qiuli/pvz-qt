#include "chilipepper.h"
#include "zombie.h"
#include "flameeffect.h"
chilipepper::chilipepper() {
    atk = 1800;
    hp = 800;
    time = 0;
    counter = 0;
    state = 0;
    setMovie(":/new/prefix1/chilipepper.gif");
}


    QRectF chilipepper::boundingRect() const
    {
        return QRectF(-35,-35,70,70);
    }

    void chilipepper::advance(int phase){
        if(!phase)
            return;
        update();
        if(hp <= 0)
            delete this;
        else if(state == 0 && mQMovie ->currentFrameNumber() == mQMovie->frameCount() -1 ){
            state = 1;
            // setMovie(":/new/prefix1/chilipepperAttack");
            flameeffect *flame = new flameeffect(y());
            scene()->addItem(flame);
            QList<QGraphicsItem *> items = scene()->items();
            foreach (QGraphicsItem *item,items){
                if(item->type() == zombie::Type && qFuzzyCompare(item->y(),y())){
                    zombie *zom = qgraphicsitem_cast<zombie *>(item);
                    zom->hp -= atk;
                    if(zom->hp <= 0){
                        zom->state = 3;
                        zom->setMovie(":/new/prefix1/Burn.gif");
                    }
                }
            }
        }
        else if (state == 1 && mQMovie->currentFrameNumber() == mQMovie->frameCount() -1)
            delete this;
    }

    bool chilipepper::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const{
        Q_UNUSED(mode)
        return other->type() == zombie::Type && qFuzzyCompare(other->y(),y());
    }


    QString chilipepper::getInfo() const
    {
    QString s = QString("血量值：%1 ,攻击值: %2 ").arg(hp) .arg(atk);
        return s;
    }
