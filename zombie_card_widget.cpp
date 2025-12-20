#include "zombie_card_widget.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QStyle>

ZombieCardWidget::ZombieCardWidget(const ZombieMeta& meta, QWidget* parent)
    : QFrame(parent), m_meta(meta) {

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(92, 118);

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(8, 8, 8, 6);
    root->setSpacing(4);

    // ⚠️ 注意：必须先 new QLabel 再 addWidget（你 plant 版本里这里有个顺序问题）
    m_icon = new QLabel(this);
    m_icon->setAlignment(Qt::AlignCenter);
    m_icon->setFixedSize(70, 58);
    root->addWidget(m_icon, 0, Qt::AlignCenter);

    const QString iconPath = meta.cardIconPath.isEmpty() ? meta.portraitPath : meta.cardIconPath;
    QPixmap pix(iconPath);
    if (!pix.isNull()) {
        m_icon->setPixmap(pix.scaled(m_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    m_tag = new QLabel(QString("HP %1").arg(meta.hp), this);
    m_tag->setObjectName("CardTag");
    m_tag->setAlignment(Qt::AlignCenter);

    auto *bottom = new QHBoxLayout();
    bottom->setContentsMargins(0, 0, 0, 0);
    bottom->setSpacing(0);
    bottom->addWidget(m_tag, 0, Qt::AlignLeft | Qt::AlignBottom);
    bottom->addStretch(1);
    root->addLayout(bottom);

    setChecked(false);
    setLocked(!meta.unlocked);
}

void ZombieCardWidget::setChecked(bool on) {
    setProperty("checked", on);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void ZombieCardWidget::setLocked(bool locked) {
    setProperty("locked", locked);
    setEnabled(!locked);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void ZombieCardWidget::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && isEnabled()) emit clicked(m_meta.id);
    QFrame::mousePressEvent(e);
}
