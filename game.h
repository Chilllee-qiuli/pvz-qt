#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>

class PauseButton; // 前向声明

class game : public QWidget
{
    Q_OBJECT
public:
    QSound* mQSound;
    QTimer* mQTimer;
    QGraphicsView* view;
    QGraphicsScene* scene;
    PauseButton* pauseBtn;
    double mScaleFactor;
    explicit game(QWidget *parent = nullptr);
    ~game() override;
    void addZombie();
    void check();

signals:

};


#endif // GAME_H
