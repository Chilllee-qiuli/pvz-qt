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
#include <QString>
#include <QPixmap>
#include <QStandardItemModel>
#include <QListView>
#include <QLabel>
#include <QFormLayout>


// 植物图鉴数据模型
struct PlantInfo {
    QString name;          // 植物名称（如“豌豆射手”）
    int hp;                // 生命值
    int atk;               // 攻击力（无攻击则为0，如向日葵）
    int cost;              // 阳光消耗
    QString skill;         // 技能描述（支持换行）
    QString imagePath;     // 图片路径（从 images 文件夹读取，如“:/images/plants/peashot.gif”）
    QString category;      // 分类（“攻击类”“防御类”“辅助类”）
    bool isUnlocked;       // 解锁状态（可选，未解锁则灰色显示）
};

class PlantShowWidget : public QWidget {
    Q_OBJECT
public:
    // ... 原有代码 ...
private:
    // 数据模型
    QStandardItemModel *m_plantModel;  // 管理植物列表数据
    QList<PlantInfo> m_allPlantInfos;  // 存储所有植物的图鉴数据
    void showPlant(const QString& plantClassName, const QString& imagePath, const QString& plantName);

    // UI 控件（需在 UI 文件中关联，或代码创建）
    QComboBox *m_categoryBox;    // 分类筛选框
    QLineEdit *m_searchEdit;     // 搜索框
    QListView *m_plantListView;  // 植物列表
    QLabel *m_plantImgLabel;     // 植物图片
    QFormLayout *m_attrLayout;   // 属性布局（展示 hp/atk 等）

    // 初始化函数
    void initPlantData();        // 加载所有植物的图鉴数据
    void initModel();            // 初始化列表模型
    void updateDetail(const QModelIndex &index);  // 选中列表项后更新详情区
    void filterPlants(const QString &category, const QString &searchText);  // 筛选植物
};


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
