#ifndef FLAMEEFFECT_H
#define FLAMEEFFECT_H
#include <QGraphicsItem>
#include <QMovie>
class flameeffect :public QGraphicsItem
{
public:
    flameeffect(qreal yPos);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem* option,QWidget* widget ) override;
    void advance(int phase) override;

private:
    QMovie *mQMovie;
    qreal yPosition;
};




#endif // FLAMEEFFECT_H
