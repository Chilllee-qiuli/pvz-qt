#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    void playBgm(const QString& resPath);
    void stopBgm();
private:
    QMediaPlayer* bgmPlayer = nullptr;
    QMediaPlaylist* bgmPlaylist = nullptr; // 新增播放列表
signals:

};


#endif // GAME_H
