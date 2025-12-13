#ifndef ZOMBIESHOW_H
#define ZOMBIESHOW_H

#include <QDialog>
#include<QGraphicsScene>
#include "zombie.h"
#include "basiczombie.h"
#include "bucketzombie.h"
#include "conezombie.h"
#include "footballzombie.h"
#include "screenzombie.h"

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

private slots:

    void on_pushButton_sunflower_clicked();

    void on_pushButton_nullwall_clicked();

    void on_pushButton_peashooter_clicked();

    void on_pushButton_potato_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::ZombieShow *ui;
    void showZombieInfo(zombie* zombie, const QString& zombieName);
};


#endif // ZOMBIESHOW_H
