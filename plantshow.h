#ifndef PLANTSHOW_H
#define PLANTSHOW_H

#include <QDialog>
#include<QGraphicsScene>
#include "plant.h"
#include "cherry.h"
#include "chilipepper.h"
#include "chomper.h"
#include "potato.h"
#include "repeater.h"
#include "snowpea.h"
#include "sunflower.h"
#include "wallnut.h"
#include "pea.h"
#include "thorn.h"

namespace Ui {
class PlantShow;
}

class PlantShow : public QDialog
{
    Q_OBJECT

public:
    QGraphicsScene* scene;
    explicit PlantShow(QWidget *parent = nullptr);
    ~PlantShow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_thorn_clicked(); // 我与她风格不同，用名字区分的开一点
private:
    Ui::PlantShow *ui;
    void showPlantInfo(plant* plant, const QString& plantName);
};


#endif // PLANTSHOW_H
