#include "plant_registry.h"

PlantRegistry& PlantRegistry::instance() {
    static PlantRegistry inst;
    return inst;
}

void PlantRegistry::registerPlant(const PlantMeta& meta) {
    // 如果重复注册同 id，就覆盖
    for (auto &p : m_plants) {
        if (p.id == meta.id) { p = meta; return; }
    }
    m_plants.push_back(meta);
}

QVector<PlantMeta> PlantRegistry::plants() const { return m_plants; }

const PlantMeta* PlantRegistry::find(const QString& id) const {
    for (const auto &p : m_plants) if (p.id == id) return &p;
    return nullptr;
}
