#include "zombie_book_dialog.h"

#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>

ZombieBookDialog::ZombieBookDialog(QWidget* parent) : QDialog(parent) {
    setObjectName("ZombieBookDialog");
    setWindowTitle("图鉴——僵尸");
    setFixedSize(800, 600);

    buildUi();
    applyQss();
    reloadFromRegistry();

    connect(m_close, &QPushButton::clicked, this, [this](){
        emit requestBackToStart();
        close();
    });
}

void ZombieBookDialog::applyQss() {
    // 你可以直接复用 plant_book.qss，也可以用我给的 zombie_book.qss
    QFile f(":/zombie_book.qss");
    if (f.open(QIODevice::ReadOnly)) {
        setStyleSheet(QString::fromUtf8(f.readAll()));
    }
}

void ZombieBookDialog::buildUi() {
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(18, 14, 18, 14);
    root->setSpacing(10);

    // Header
    m_headerBar = new QFrame(this);
    m_headerBar->setObjectName("HeaderBar");
    m_headerBar->setFixedHeight(56);
    auto *hLay = new QHBoxLayout(m_headerBar);
    hLay->setContentsMargins(14, 8, 14, 8);

    m_headerTitle = new QLabel("图鉴——僵尸", m_headerBar);
    m_headerTitle->setObjectName("HeaderTitle");
    m_headerTitle->setAlignment(Qt::AlignCenter);
    hLay->addWidget(m_headerTitle);

    root->addWidget(m_headerBar);

    // Middle
    auto *mid = new QHBoxLayout();
    mid->setSpacing(14);

    // Left cards
    m_cardScroll = new QScrollArea(this);
    m_cardScroll->setObjectName("CardScroll");
    m_cardScroll->setWidgetResizable(true);
    m_cardScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_cardScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_cardPane = new QWidget(m_cardScroll);
    m_cardPane->setObjectName("CardPane");
    m_flow = new FlowLayout(m_cardPane, 6, 10, 10);
    m_cardPane->setLayout(m_flow);

    m_cardScroll->setWidget(m_cardPane);
    m_cardScroll->setFixedWidth(220);

    // Right detail
    m_detailOuter = new QFrame(this);
    m_detailOuter->setObjectName("DetailOuter");
    auto *outerLay = new QVBoxLayout(m_detailOuter);
    outerLay->setContentsMargins(12, 12, 12, 12);

    m_detailInner = new QFrame(m_detailOuter);
    m_detailInner->setObjectName("DetailInner");
    auto *innerLay = new QVBoxLayout(m_detailInner);
    innerLay->setContentsMargins(12, 12, 12, 12);
    innerLay->setSpacing(10);

    m_portraitFrame = new QFrame(m_detailInner);
    m_portraitFrame->setObjectName("PortraitFrame");
    m_portraitFrame->setFixedHeight(170);
    auto *pLay = new QVBoxLayout(m_portraitFrame);
    pLay->setContentsMargins(10, 10, 10, 10);

    m_portrait = new QLabel(m_portraitFrame);
    m_portrait->setAlignment(Qt::AlignCenter);
    pLay->addWidget(m_portrait);

    m_name = new QLabel("—", m_detailInner);
    m_name->setObjectName("ZombieName");
    m_name->setAlignment(Qt::AlignCenter);

    m_tabs = new QTabWidget(m_detailInner);
    m_tabs->setTabPosition(QTabWidget::East);

    m_introText = new QTextBrowser(m_tabs);
    m_introText->setFrameShape(QFrame::NoFrame);
    m_introText->setOpenExternalLinks(false);

    auto *placeholder = new QWidget(m_tabs);
    m_tabs->addTab(m_introText, "简介");
    m_tabs->addTab(placeholder, "掉落");

    innerLay->addWidget(m_portraitFrame);
    innerLay->addWidget(m_name);
    innerLay->addWidget(m_tabs, 1);

    outerLay->addWidget(m_detailInner, 1);

    mid->addWidget(m_cardScroll);
    mid->addWidget(m_detailOuter, 1);

    root->addLayout(mid, 1);

    // Bottom
    auto *bottom = new QHBoxLayout();
    bottom->addStretch();

    m_close = new QPushButton("返回", this);
    m_close->setObjectName("BottomBtn");
    bottom->addWidget(m_close);

    root->addLayout(bottom);
}

void ZombieBookDialog::reloadFromRegistry() {
    rebuildCards(ZombieRegistry::instance().zombies());
}

void ZombieBookDialog::rebuildCards(const QVector<ZombieMeta>& zombies) {
    while (m_flow->count() > 0) {
        auto *it = m_flow->takeAt(0);
        delete it->widget();
        delete it;
    }
    m_cardById.clear();
    m_selectedId.clear();

    for (const auto &z : zombies) {
        auto *card = new ZombieCardWidget(z, m_cardPane);
        connect(card, &ZombieCardWidget::clicked, this, &ZombieBookDialog::onCardClicked);
        m_flow->addWidget(card);
        m_cardById.insert(z.id, card);

        if (m_selectedId.isEmpty() && z.unlocked) m_selectedId = z.id;
    }

    if (!m_selectedId.isEmpty()) onCardClicked(m_selectedId);
}

void ZombieBookDialog::onCardClicked(const QString& id) {
    const ZombieMeta* meta = ZombieRegistry::instance().find(id);
    if (!meta) return;

    if (!m_selectedId.isEmpty() && m_cardById.contains(m_selectedId))
        m_cardById[m_selectedId]->setChecked(false);

    m_selectedId = id;
    if (m_cardById.contains(id)) m_cardById[id]->setChecked(true);

    showDetail(*meta);
}

void ZombieBookDialog::showDetail(const ZombieMeta& meta) {
    m_name->setText(meta.name);

    // 图（支持 gif）
    if (m_movie) { delete m_movie; m_movie = nullptr; }
    if (meta.portraitPath.endsWith(".gif", Qt::CaseInsensitive)) {
        m_movie = new QMovie(meta.portraitPath, QByteArray(), this);
        m_portrait->setMovie(m_movie);
        m_movie->start();
    } else {
        QPixmap pix(meta.portraitPath);
        if (!pix.isNull()) {
            m_portrait->setPixmap(pix.scaled(m_portraitFrame->size() * 0.85,
                                             Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            m_portrait->setText("图片缺失");
        }
    }

    // 你的 zombie 子类里 atk/speed 通常是“每帧”数值（33ms 一帧）
    const double atkPerSec = meta.atk * 1000.0 / 33.0;
    const double spdPerSec = meta.speed * 1000.0 / 33.0;

    QString html;
    if (!meta.desc.isEmpty()) {
        html += QString("<b>%1</b><br>").arg(meta.desc.toHtmlEscaped());
    }
    html += "<hr>";
    html += QString("韧性：<b>%1</b><br>").arg(meta.hp);
    html += QString("攻击：<b>%1</b> /帧（≈ %2 /秒）<br>").arg(meta.atk).arg(atkPerSec, 0, 'f', 1);
    html += QString("速度：<b>%1</b> px/帧（≈ %2 px/秒）<br>").arg(meta.speed, 0, 'f', 3).arg(spdPerSec, 0, 'f', 1);

    m_introText->setHtml(html);
}
