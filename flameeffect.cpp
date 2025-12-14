#include "flameeffect.h"
#include <QPainter>

flameeffect::flameeffect(qreal yPos)
    :yPosition(yPos)
{
    mQMovie = new QMovie(":/new/prefix1/chilipepperAttack.gif");
    mQMovie->start();
    setPos(0,yPos -20);
}

QRectF flameeffect::boundingRect()const{
    return QRectF(200,-20,1000,100);
}


void flameeffect::paint(QPainter *painter,const QStyleOptionGraphicsItem* option,QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(mQMovie->state() == QMovie::Running){
        QImage frame = mQMovie->currentImage();
        painter->drawImage(boundingRect(),frame);
    }
}

void flameeffect::advance(int phase){
    if(!phase) return;
    if(mQMovie->currentFrameNumber() == mQMovie->frameCount()-1){
        delete this;
    }
}
