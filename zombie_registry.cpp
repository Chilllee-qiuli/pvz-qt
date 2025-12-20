#include "zombie_registry.h"

ZombieRegistry& ZombieRegistry::instance() {
    static ZombieRegistry inst;
    return inst;
}

void ZombieRegistry::registerZombie(const ZombieMeta& meta) {
    // 如果重复注册同 id，就覆盖
    for (auto &z : m_zombies) {
        if (z.id == meta.id) { z = meta; return; }
    }
    m_zombies.push_back(meta);
}

QVector<ZombieMeta> ZombieRegistry::zombies() const { return m_zombies; }

const ZombieMeta* ZombieRegistry::find(const QString& id) const {
    for (const auto &z : m_zombies) if (z.id == id) return &z;
    return nullptr;
}
