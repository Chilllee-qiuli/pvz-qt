#ifndef ZOMBIESHOW_H
#define ZOMBIESHOW_H

#include <QDialog>
#include <QGraphicsScene>
#include "zombie.h"
#include "basiczombie.h"
#include "bucketzombie.h"
#include "conezombie.h"
#include "footballzombie.h"
#include "screenzombie.h"
#include "flagzombie.h"

namespace Ui {
class ZombieShow;
}

class ZombieShow : public QDialog
{
    Q_OBJECT

public:
    QGraphicsScene* scene;
    explicit ZombieShow(QWidget *parent = nullptr);
    ~ZombieShow();

    // 统一处理僵尸攻击动画
    static void playAttackAnimation(zombie* zombie);
    
    // 统一处理僵尸死亡动画
    static void playDeathAnimation(zombie* zombie);

private slots:
    void on_pushButton_sunflower_clicked();
    void on_pushButton_nullwall_clicked();
    void on_pushButton_peashooter_clicked();
    void on_pushButton_potato_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    void on_pushButton_flag_clicked();

private:
    Ui::ZombieShow *ui;
    void showZombieInfo(zombie* zombie, const QString& zombieName);
};

#endif // ZOMBIESHOW_H
