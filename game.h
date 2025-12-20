#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
class PauseButton; // 前向声明

class game : public QWidget
{
    Q_OBJECT
public:
    QSound* mQSound = nullptr;

    QTimer* mQTimer;
    QGraphicsView* view;
    QGraphicsScene* scene;
    PauseButton* pauseBtn;
    double mScaleFactor;
    int elapsedMs;  // 将elapsedMs作为类成员变量
    explicit game(QWidget *parent = nullptr);
    ~game() override;
    void addZombie();
    void check();
    void playBgm(const QString& resPath);
    void stopBgm();
    void resetGameTime();  // 添加重置游戏时间的方法
private:
    QMediaPlayer* bgmPlayer = nullptr;
    QMediaPlaylist* bgmPlaylist = nullptr; // 新增播放列表
protected:
    //bool eventFilter(QObject* watched, QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override; // 可选：ESC 取消

};


#endif // GAME_H
