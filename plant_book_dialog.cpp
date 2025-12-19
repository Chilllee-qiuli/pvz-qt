#include "plant_book_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>

PlantBookDialog::PlantBookDialog(QWidget* parent) : QDialog(parent) {
    setObjectName("PlantBookDialog");
    setWindowTitle("图鉴——植物");
    setFixedSize(800, 600);

    buildUi();
    applyQss();
    reloadFromRegistry();

    connect(m_close, &QPushButton::clicked, this, [this](){
        emit requestBackToStart();
        close();
    });
}

void PlantBookDialog::applyQss() {
    QFile f(":/plant_book.qss");   // ✅ 改这里
    if (f.open(QIODevice::ReadOnly)) {
        setStyleSheet(QString::fromUtf8(f.readAll()));
    } else {
        qDebug() << "QSS open failed:" << f.errorString();
    }
}


void PlantBookDialog::buildUi() {
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(18, 14, 18, 14);
    root->setSpacing(10);

    // Header
    m_headerBar = new QFrame(this);
    m_headerBar->setObjectName("HeaderBar");
    m_headerBar->setFixedHeight(56);
    auto *hLay = new QHBoxLayout(m_headerBar);
    hLay->setContentsMargins(14, 8, 14, 8);

    m_headerTitle = new QLabel("图鉴——植物", m_headerBar);
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

    // Right detail (outer wood frame)
    m_detailOuter = new QFrame(this);
    m_detailOuter->setObjectName("DetailOuter");
    auto *outerLay = new QVBoxLayout(m_detailOuter);
    outerLay->setContentsMargins(12, 12, 12, 12);

    m_detailInner = new QFrame(m_detailOuter);
    m_detailInner->setObjectName("DetailInner");
    auto *innerLay = new QVBoxLayout(m_detailInner);
    innerLay->setContentsMargins(12, 12, 12, 12);
    innerLay->setSpacing(10);

    // portrait
    m_portraitFrame = new QFrame(m_detailInner);
    m_portraitFrame->setObjectName("PortraitFrame");
    m_portraitFrame->setFixedHeight(170);
    auto *pLay = new QVBoxLayout(m_portraitFrame);
    pLay->setContentsMargins(10, 10, 10, 10);

    m_portrait = new QLabel(m_portraitFrame);
    m_portrait->setAlignment(Qt::AlignCenter);
    pLay->addWidget(m_portrait);

    m_name = new QLabel("—", m_detailInner);
    m_name->setObjectName("PlantName");
    m_name->setAlignment(Qt::AlignCenter);

    // tabs (简介/装扮)
    m_tabs = new QTabWidget(m_detailInner);
    m_tabs->setTabPosition(QTabWidget::East);

    m_introText = new QTextBrowser(m_tabs);
    m_introText->setFrameShape(QFrame::NoFrame);
    m_introText->setOpenExternalLinks(false);

    auto *cosmetic = new QWidget(m_tabs); // 先占位，后续你真要做“装扮”再扩展

    m_tabs->addTab(m_introText, "简介");
    m_tabs->addTab(cosmetic, "装扮");

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
    connect(m_close, &QPushButton::clicked, this, &QDialog::close);
    bottom->addWidget(m_close);

    root->addLayout(bottom);
}

void PlantBookDialog::reloadFromRegistry() {
    rebuildCards(PlantRegistry::instance().plants());
}

void PlantBookDialog::rebuildCards(const QVector<PlantMeta>& plants) {
    // 清空旧卡片
    while (m_flow->count() > 0) {
        auto *it = m_flow->takeAt(0);
        delete it->widget();
        delete it;
    }
    m_cardById.clear();
    m_selectedId.clear();

    // 新建卡片
    for (const auto &p : plants) {
        auto *card = new PlantCardWidget(p, m_cardPane);
        connect(card, &PlantCardWidget::clicked, this, &PlantBookDialog::onCardClicked);
        m_flow->addWidget(card);
        m_cardById.insert(p.id, card);

        if (m_selectedId.isEmpty() && p.unlocked) m_selectedId = p.id;
    }

    // 默认选中第一个
    if (!m_selectedId.isEmpty()) onCardClicked(m_selectedId);
}

void PlantBookDialog::onCardClicked(const QString& id) {
    const PlantMeta* meta = PlantRegistry::instance().find(id);
    if (!meta) return;

    // 更新选中态
    if (!m_selectedId.isEmpty() && m_cardById.contains(m_selectedId))
        m_cardById[m_selectedId]->setChecked(false);

    m_selectedId = id;
    if (m_cardById.contains(id)) m_cardById[id]->setChecked(true);

    showDetail(*meta);
}

void PlantBookDialog::showDetail(const PlantMeta& meta) {
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

    // 简介内容（你也可以拼成你截图里“韧性/生产/范围”等格式）
    QString html;
    html += QString("<b>%1</b><br>").arg(meta.desc.toHtmlEscaped());
    html += "<hr>";
    html += QString("韧性：<b>%1</b><br>").arg(meta.hp);
    html += QString("攻击：<b>%1</b><br>").arg(meta.atk);
    html += QString("花费：<b>%1</b><br>").arg(meta.cost);
    html += QString("冷却：<b>%1</b> 秒<br>").arg(meta.cooldown);
    m_introText->setHtml(html);
}
