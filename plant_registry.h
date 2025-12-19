#pragma once
#include <QString>
#include <QVector>
#include <functional>

class plant; // 你项目里的基类

struct PlantMeta {
    QString id;           // "pea", "sunflower"
    QString name;         // "豌豆射手"
    QString cardIconPath; // 卡片小图（或直接用 portraitPath 缩略）
    QString portraitPath; // 右侧大图/动态图(gif)
    int hp = 0;
    int atk = 0;
    int cost = 0;
    double cooldown = 0;  // 秒
    QString desc;         // 简介（可多行）
    bool unlocked = true;

    // 可选：如果你还想复用 plant::getInfo()，就提供工厂
    std::function<plant*()> factory; // new 某植物
};

class PlantRegistry {
public:
    static PlantRegistry& instance();

    void registerPlant(const PlantMeta& meta);
    QVector<PlantMeta> plants() const;
    const PlantMeta* find(const QString& id) const;

private:
    PlantRegistry() = default;
    QVector<PlantMeta> m_plants;
};
