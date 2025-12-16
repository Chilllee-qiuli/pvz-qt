#include "game.h"
#include "shop.h"
#include "map.h"
#include "shovel.h"
#include "pausebutton.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include "zombie.h"
#include "mower.h"
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>


game::game(QWidget *parent)
    : QWidget{parent}
{
    mQSound=new QSound(":/new/prefix2/Grazy.wav");
    mQSound->play();
    mQTimer=new QTimer(this);

    scene=new QGraphicsScene(this);
    scene->setSceneRect(150,0,900,600);//控制img需要截取部分
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //视图显示的坐标，注意所有的坐标都是基于未被裁剪图片的坐标
    //(290,120,10,10);(1,1)坐标(中心坐标)
    //245,175->330,270->>>>格子85 95
    //shop是那个部分
    //应该是上面选择植物的那栏
    shop *sh = new shop;
    sh->setPos(520, 45);
    scene->addItem(sh);
    //右上角铁锹
    shovel *sho = new shovel;
    sho->setPos(830, 40);
    scene->addItem(sho);
    //暂停按钮
    pauseBtn = new PauseButton(this);
    pauseBtn->setPos(900, 30);
    scene->addItem(pauseBtn);
    //地图，就是草坪
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);

    //小推车
    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;
        mower->setPos(215, 120 + 95 * i);
        scene->addItem(mower);
    }

    // 创建视图对象并设置属性
    view = new QGraphicsView(scene, this);
    view->resize(900, 600);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/new/prefix1/Background.jpg")); // 设置背景图片
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    // 连接计时器的timeout信号到场景的advance槽，实现场景中物体的动画效果
    connect(mQTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    // 连接计时器的timeout信号到游戏的addZombie槽，添加僵尸
    connect(mQTimer, &QTimer::timeout, this, &game::addZombie);
    // 连接计时器的timeout信号到游戏的check槽，检查游戏是否结束
    connect(mQTimer, &QTimer::timeout, this, &game::check);
    mQTimer->start(33); // 启动计时器，每33毫秒触发一次timeout信号，驱动游戏动画效果

    view->show(); // 显示视图
}
game::~game()
{
    delete mQSound;
    delete mQTimer;
    delete view;
    delete scene;
}

void game::addZombie()
{
    // 假设外部 QTimer 每 33ms 调一次
    constexpr int kTickMs = 33;

    // ========== 工具：生成一只指定类型僵尸 ==========
    enum class ZType { Basic, Cone, Bucket, Screen, Football };

    auto spawnOne = [&](ZType t, int row) {
        zombie* zom = nullptr;
        switch (t) {
        case ZType::Basic:    zom = new basiczombie;    break;
        case ZType::Cone:     zom = new ConeZombie;     break;
        case ZType::Bucket:   zom = new BucketZombie;   break;
        case ZType::Screen:   zom = new ScreenZombie;   break;
        case ZType::Football: zom = new FootballZombie; break;
        }
        zom->setPos(1028, 120 + 95 * row);
        scene->addItem(zom);
    };

    auto randRow = [&]() { return qrand() % 5; };

    // ========== 运行时状态（static：只在本函数内保存） ==========
    static int elapsedMs = 0;
    elapsedMs += kTickMs;

    // --------------------------------------------------------------------
    // A) 正常刷怪：永远存在（负责“发育期 + 难度爬坡”）
    // --------------------------------------------------------------------
    // 思路：用 elapsedMs 计算当前“基础生成间隔 maxtime(帧数)”和“强怪比例”
    // 你可以随便调这些常量来改手感。

    auto spawnNormal = [&]() {
        // 1) 发育保护：前 50 秒非常慢且只出普通（避免开局崩）
        //    之后逐步加速，直到一个下限（别快到离谱）
        const int t = elapsedMs;

        int maxtimeFrames = 0; // “最大间隔”（单位：tick次数）
        if (t < 50000) {
            // 约 8~14 秒一只（250~420 帧）
            maxtimeFrames = 250 + (qrand() % 171);
        } else {
            // 50s 之后开始爬坡：从 ~6s 一只慢慢加速到 ~1.2s 一只
            // 6s ≈ 6000/33 ≈ 182 帧；1.2s ≈ 36 帧
            // 用线性/分段都行，这里用简单线性 + clamp
            int progressed = (t - 50000);           // 从 0 开始爬坡
            int start = 182;
            int end   = 36;
            int duration = 200000;                  // 用 200s 逐渐爬到最强（可调）
            int delta = (start - end);
            int reduce = (int)((1.0 * progressed / duration) * delta);
            if (reduce < 0) reduce = 0;
            if (reduce > delta) reduce = delta;
            maxtimeFrames = start - reduce;
        }

        // 2) 带随机的实际间隔 timeFrames（防止固定节奏）
        //    取 [maxtime/2 , maxtime] 之间
        static int counter = 0;
        static int timeFrames = 0;
        if (timeFrames <= 0) timeFrames = maxtimeFrames;

        if (++counter >= timeFrames) {
            counter = 0;
            timeFrames = (maxtimeFrames / 2) + (qrand() % (maxtimeFrames - maxtimeFrames / 2 + 1));

            // 3) 正常刷怪类型随时间变硬（但不要太激进）
            int r = qrand() % 100;

            if (t < 50000) {
                // 发育期只出普通
                spawnOne(ZType::Basic, randRow());
                return;
            }

            // 50s 后：逐渐提高硬怪占比
            // 这里用时间分段控制概率（很好调）
            if (t < 100000) {
                // 50~100s：普通多、路障少、铁桶极少
                if (r < 70) spawnOne(ZType::Basic, randRow());
                else if (r < 95) spawnOne(ZType::Cone, randRow());
                else spawnOne(ZType::Bucket, randRow());
            } else if (t < 200000) {
                // 100~200s：开始出现铁桶/读报，橄榄球少量
                if (r < 45) spawnOne(ZType::Basic, randRow());
                else if (r < 75) spawnOne(ZType::Cone, randRow());
                else if (r < 90) spawnOne(ZType::Bucket, randRow());
                else if (r < 97) spawnOne(ZType::Screen, randRow());
                else spawnOne(ZType::Football, randRow());
            } else {
                // 200s+：偏后期
                if (r < 25) spawnOne(ZType::Basic, randRow());
                else if (r < 55) spawnOne(ZType::Cone, randRow());
                else if (r < 80) spawnOne(ZType::Bucket, randRow());
                else if (r < 92) spawnOne(ZType::Screen, randRow());
                else spawnOne(ZType::Football, randRow());
            }
        }
    };

    // --------------------------------------------------------------------
    // B) 波次刷怪：到点“额外加餐”（不会影响正常刷怪）
    // --------------------------------------------------------------------
    // 设计：波次以“触发时间”启动，然后在 duration 内按 burst 节奏喷出 total 只
    // 这会在正常刷怪基础上叠加，因此就是你要的“辅助波次”。

    struct Rule { ZType type; int weight; };
    struct WaveCfg {
        int triggerMs;     // 触发时间
        int durationMs;    // 在这段时间内把 total 刷完（越短越像“大波”）
        int total;         // 额外刷多少只
        int burstEveryMs;  // 每隔多少 ms 喷一次（例如 300ms 一喷）
        int burstCount;    // 每次喷几只（例如 3 只）
        Rule rules[5];
        int ruleCount;
    };
    struct WaveState {
        bool active = false;
        bool done = false;
        int startMs = 0;
        int remain = 0;
        int accMs = 0;
    };

    // 你只需要改这里的表，就能改“旗帜波时间点和强度”
    static const WaveCfg waveCfgs[] = {
        // 触发  ,持续 ,总数,喷发间隔,每次喷几只, 权重...
        // 第一波怪太超模了去掉吧
        { 145000,  7000, 18,   350,     2, { {ZType::Cone,50},{ZType::Bucket,35},{ZType::Basic,15} }, 3 }, // 第一旗帜波
        { 175000,  8000, 26,   320,     3, { {ZType::Cone,35},{ZType::Bucket,40},{ZType::Screen,15},{ZType::Basic,10} }, 4 },
        {210000,  9000, 34,   280,     4, { {ZType::Bucket,35},{ZType::Screen,25},{ZType::Football,15},{ZType::Cone,25} }, 4 }, // 大波
        // 继续加：{ triggerMs, durationMs, total, burstEveryMs, burstCount, rules..., ruleCount }
    };
    static const int waveCount = sizeof(waveCfgs) / sizeof(waveCfgs[0]);
    static WaveState waveStates[32]; // waveCount <= 32 即可

    auto pickByWeight = [&](const WaveCfg& cfg) -> ZType {
        int sum = 0;
        for (int i = 0; i < cfg.ruleCount; ++i) sum += (cfg.rules[i].weight > 0 ? cfg.rules[i].weight : 0);
        if (sum <= 0) return ZType::Basic;
        int r = qrand() % sum;
        for (int i = 0; i < cfg.ruleCount; ++i) {
            int w = (cfg.rules[i].weight > 0 ? cfg.rules[i].weight : 0);
            if (r < w) return cfg.rules[i].type;
            r -= w;
        }
        return cfg.rules[cfg.ruleCount - 1].type;
    };

    auto spawnWaves = [&]() {
        for (int i = 0; i < waveCount; ++i) {
            const WaveCfg& cfg = waveCfgs[i];
            WaveState& st = waveStates[i];

            if (st.done) continue;

            // 触发
            if (!st.active) {
                if (elapsedMs < cfg.triggerMs) continue;
                st.active = true;
                st.startMs = elapsedMs;
                st.remain = cfg.total;
                st.accMs = 0;
            }

            // 到期或刷完
            int age = elapsedMs - st.startMs;
            if (st.remain <= 0 || age >= cfg.durationMs) {
                st.done = true;
                st.active = false;
                continue;
            }

            // 按 burstEveryMs 喷发
            st.accMs += kTickMs;
            while (st.accMs >= cfg.burstEveryMs && st.remain > 0) {
                st.accMs -= cfg.burstEveryMs;

                int batch = cfg.burstCount;
                if (batch < 1) batch = 1;
                if (batch > st.remain) batch = st.remain;

                // 额外生成 batch 只（叠加到正常刷怪之上）
                for (int k = 0; k < batch; ++k) {
                    spawnOne(pickByWeight(cfg), randRow());
                }
                st.remain -= batch;
            }
        }
    };

    // ================== 最终执行顺序：正常 + 波次叠加 ==================
    spawnNormal(); // 基础节奏：发育+爬坡（永远有）
    spawnWaves();  // 额外节奏：旗帜波/大波（到点加餐）
}


void game::check()
{
    // 检查游戏是否结束，是否有僵尸到达屏幕最左边
    const QList<QGraphicsItem *> items = scene->items();
    foreach (QGraphicsItem *item, items)
    {
        if (item->type() == zombie::Type && item->x() < 150)
        {
            // 如果有僵尸到达屏幕最左边，游戏结束
            scene->addPixmap(QPixmap(":/new/prefix1/ZombiesWon.png"))->setPos(336, 92);
            scene->advance();
            mQTimer->stop(); // 停止计时器，结束游戏
            return;
        }
    }
}
