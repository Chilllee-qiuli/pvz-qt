#pragma once

#include <QString>
#include <QVector>
#include <functional>

class zombie; // 你项目里的僵尸基类

// 僵尸图鉴用的元信息（和 PlantMeta 思路一致）
struct ZombieMeta {
    QString id;           // "basic", "cone" ...
    QString name;         // "普通僵尸" ...
    QString cardIconPath; // 左侧卡片小图（可为空，默认用 portraitPath）
    QString portraitPath; // 右侧大图/动态图(gif)

    int hp = 0;
    int atk = 0;          // 每帧伤害（你的代码里经常是 100*33/1000）
    double speed = 0.0;   // 每帧位移（像素/帧）

    QString desc;         // 简介（可多行）
    bool unlocked = true;

    // 可选：如果你希望点击图鉴还能生成实体，就提供工厂（目前用不到可置空）
    std::function<zombie*()> factory;
};

class ZombieRegistry {
public:
    static ZombieRegistry& instance();

    void registerZombie(const ZombieMeta& meta);
    QVector<ZombieMeta> zombies() const;
    const ZombieMeta* find(const QString& id) const;

private:
    ZombieRegistry() = default;
    QVector<ZombieMeta> m_zombies;
};
