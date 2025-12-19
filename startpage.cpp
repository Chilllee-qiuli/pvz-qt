#include "startpage.h"
#include <QIcon>
#include <QPushButton>
#include "game.h"
#include "plantshow.h"
#include "bgmmanager.h"
#include "zombieshow.h"
#include "plant_book_dialog.h"
#include "plant_registry.h"


static void ensurePlantRegistryInited() {
    static bool inited = false;
    if (inited) return;
    inited = true;

    auto &r = PlantRegistry::instance();

    // 1) 豌豆射手
    r.registerPlant(PlantMeta{
        "pea",
        "豌豆射手",
        ":/new/prefix1/Peashooter.png",   // 卡片小图（没有 card_ 图就先用这个）
        ":/new/prefix1/Peashooter.png",   // 右侧大图/预览
        200,                              // hp（来自 pea.cpp）
        40,                               // atk（来自 pea.cpp）
        100,                              // cost（手填：原版 100）
        7.5,                              // cooldown（手填：你项目里常用 7.5）
        "攻击兼备的植物，梦开始的地方！",
        true,
        nullptr
    });

    // 2) 向日葵
    r.registerPlant(PlantMeta{
        "sunflower",
        "向日葵",
        ":/new/prefix1/SunFlower.png",
        ":/new/prefix1/SunFlower.png",
        300,                              // hp（来自 sunflower.cpp）
        0,                                // atk
        50,                               // cost（手填：原版 50）
        7.5,                              // cooldown
        "提供阳光。",
        true,
        nullptr
    });

    // 3) 坚果墙
    r.registerPlant(PlantMeta{
        "wallnut",
        "坚果墙",
        ":/new/prefix1/WallNut.png",       // 如果你资源里没有 WallNut.png，可以换成 WallNut.gif 或任意静态图
        ":/new/prefix1/WallNut.png",
        3000,                             // hp（来自 wallnut.cpp）
        0,                                // atk
        75,                               // cost（手填：原版 50）
        30.0,                             // cooldown（手填：原版较长，先 30 秒）
        "阻挡僵尸前进的坚固防线。",
        true,
        nullptr
    });

    // 4) 地刺
    r.registerPlant(PlantMeta{
        "thorn",
        "地刺",
        ":/new/prefix1/Thorn.png",         // thorn.cpp 用的就是 Thorn.png
        ":/new/prefix1/Thorn.png",
        10000,                            // hp（你写的兼容值）
        20,                               // atk（来自 thorn.cpp）
        100,                              // cost（手填：原版地刺 100）
        7.5,                              // cooldown
        "对经过的僵尸造成持续伤害。",
        true,
        nullptr
    });
    // 5) 土豆地雷（potato）
    r.registerPlant(PlantMeta{
        "potato",
        "土豆地雷",
        ":/new/prefix1/PotatoMine.png",   // potato.cpp: setMovie(":/new/prefix1/PotatoMine1.gif")
        ":/new/prefix1/PotatoMine.png",
        300,                               // potato.cpp: hp = 300
        1800,                              // potato.cpp: atk = 1800
        25,                                // cost（建议值：原版 25）
        30.0,                              // cooldown（建议值：原版偏长；你也可改小）
        "需要时间准备（约15秒），准备好后会爆炸。",
        true,
        nullptr
    });

    // 6) 樱桃炸弹（cherry）
    r.registerPlant(PlantMeta{
        "cherry",
        "樱桃炸弹",
        ":/new/prefix1/CherryBomb.gif",     // cherry.cpp: setMovie(":/new/prefix1/CherryBomb.gif")
        ":/new/prefix1/CherryBomb.gif",
        800,                               // cherry.cpp: hp = 800
        1800,                              // cherry.cpp: atk = 1800
        150,                               // cost（建议值：原版 150）
        50.0,                              // cooldown（建议值：原版较长）
        "爆炸，对周围僵尸造成巨大伤害。",
        true,
        nullptr
    });

    // 7) 火爆辣椒（chilipepper）
    r.registerPlant(PlantMeta{
        "chilipepper",
        "火爆辣椒",
        ":/new/prefix1/chilipepper.gif",    // chilipepper.cpp: setMovie(":/new/prefix1/chilipepper.gif")
        ":/new/prefix1/chilipepper.gif",
        800,                               // chilipepper.cpp: hp = 800
        1800,                              // chilipepper.cpp: atk = 1800
        50,                               // cost（建议值：原版 125）
        50.0,                              // cooldown（建议值）
        "清除整行的僵尸。",
        true,
        nullptr
    });

    // 8) 大嘴花（chomper）
    r.registerPlant(PlantMeta{
        "chomper",
        "大嘴花",
        ":/new/prefix1/Chomper_init.gif",   // chomper.cpp: setMovie(":/new/prefix1/Chomper_init.gif")
        ":/new/prefix1/Chomper_init.gif",
        400,                               // chomper.cpp: hp = 400
        1800,                              // chomper.cpp: atk = 1800
        150,                               // cost（建议值：原版 150）
        30.0,                              // cooldown（建议值：你也可改 20/40）
        "可以吞掉前方的僵尸，吞咽期间无法攻击。",
        true,
        nullptr
    });

}
startpage::startpage(QWidget *parent)
    : QWidget{parent}
{
    this->resize(900,600);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png"));
    mpainter_1=new QPainter(this);
    QPushButton* btn_1=new QPushButton(this);
    QPushButton* btn_2=new QPushButton(this);
    QPushButton* btn_3=new QPushButton(this);
    QPushButton* btn_4=new QPushButton(this);
    btn_1->setGeometry(450,60,340,120);
    btn_1->setStyleSheet("QPushButton{"
                         "border:none;" // 设置无边框
                         "padding:0px;" // 设置无内边距
                         "background:transparent;" // 设置背景透明
                         "border-image:url(:/new/prefix1/mx1.png);" // 设置按钮样式，包括背景图片
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/mx.png);" // 鼠标悬停样式
                         "}"
                         );
    btn_2->setGeometry(450,150,320,130);
    btn_2->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/jiangshitujian.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/jiangshitujian1.png);"
                         "}"
                         );
    btn_3->setGeometry(460,230,290,130);
    btn_3->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/zhiwutujian.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/plantShow.png);"
                         "}"
                         );
    btn_4->setGeometry(460,320,280,120);
    btn_4->setStyleSheet("QPushButton{"
                         "border:none;"
                         "padding:0px;"
                         "background:transparent;"
                         "border-image:url(:/new/prefix1/mini1.png);"
                         "}"
                         "QPushButton:hover{"
                         "border-image:url(:/new/prefix1/mini.png);"
                         "}"
                         );
     // 连接按钮点击事件，启动游戏窗口，并隐藏当前窗口
    connect(btn_1,&QPushButton::clicked,[this](){
        game* ga=new game;
        BgmManager::instance().play("qrc:/new/prefix2/UraniwaNi.wav"); // 换成你的战斗音乐资源路径
        ga->show();
        this->hide();
    });

    // connect(btn_3,&QPushButton::clicked,[this](){
    //     PlantShow* ps=new PlantShow;
    //     ps->show();
    //     this->hide();
    // });

    connect(btn_3, &QPushButton::clicked, [this]() {
        static bool inited = false;
        if (!inited) {
            inited = true;


        }

        setObjectName("PlantBookDialog");
        ensurePlantRegistryInited();
        auto *dlg = new PlantBookDialog(this);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        connect(dlg, &QObject::destroyed, this, [this](){ this->show(); });
        dlg->show();
        this->hide();

        // ✅ 图鉴请求返回主界面
        connect(dlg, &PlantBookDialog::requestBackToStart, this, [this]() {
            this->show();
        });

        // ✅ 无论用按钮关、点右上角 X 关，都能回主界面
        connect(dlg, &QObject::destroyed, this, [this]() {
            this->show();
        });

        dlg->show();
        this->hide();
    });

    connect(btn_2,&QPushButton::clicked,[this](){
        ZombieShow* zs = new ZombieShow;
        zs->show();
        this->hide();
    });

}

void startpage::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // 开始绘制
    QImage img(":/new/prefix1/Surface.png"); // 加载图片资源
    mpainter_1->drawImage(QRect(0, 0, 900, 600), img); // 在主窗口绘制图片
    mpainter_1->end(); // 结束绘制
}
