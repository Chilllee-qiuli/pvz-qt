// plantselectionwidget.cpp
#include "plantselectionwidget.h"


PlantSelectionWidget::PlantSelectionWidget(const QVector<QString>& allPlants, QWidget *parent)
    : QDialog(parent), allPlants(allPlants)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //上方的设置
    QWidget *containerWidget = new QWidget(this);
    containerWidget->setFixedSize(530, 90); // 设置与Shop背景图匹配的尺寸
    containerWidget->setStyleSheet("border-image: url(:/new/prefix1/Shop.png) 0 0 0 0 stretch stretch;"
                                   "background-repeat: no-repeat;"
                                   "background-position: center;");

    // 使用绝对定位而非布局管理器，精确控制按钮位置
    for (int i = 0; i < 7; ++i) {
        QPushButton *button = new QPushButton("", containerWidget);
        button->setFixedSize(60, 80);

        // 计算按钮在背景图上的精确位置（根据Shop.png调整这些值）
        int xPos = 85 + i * 62; // 每个按钮的x坐标，78是按钮间距
        int yPos = 5;          // 按钮的y坐标

        button->move(xPos, yPos);
        button->setStyleSheet("border: 1px solid gray;"
                              "border-image:none;" // 半透明背景
                              "border-radius: 5px;");

        topButtons.append(button);
        connect(button, &QPushButton::clicked, this, &PlantSelectionWidget::onPlantButtonClicked);
    }
    mainLayout->addWidget(containerWidget);
    // 底部可选植物区域保持不变
    // QHBoxLayout *bottomLayout = new QHBoxLayout;
    // // 上面一行七个空位
    // QHBoxLayout *topLayout = new QHBoxLayout;
    // for (int i = 0; i < 7; ++i) {
    //     QPushButton *button = new QPushButton("", this);
    //     button->setFixedSize(60, 80); // 设置固定大小，使界面更美观
    //     button->setStyleSheet("border: 1px solid gray;border-image:none"); // 添加边框，更容易识别空位
    //     topButtons.append(button);
    //     topLayout->addWidget(button);
    //     connect(button, &QPushButton::clicked, this, &PlantSelectionWidget::onPlantButtonClicked);
    // }
    // mainLayout->addLayout(topLayout);

    // // 下面是可以选择的植物
    // QHBoxLayout *bottomLayout = new QHBoxLayout;
    // for (const QString& plant : allPlants) {
    //     QPushButton *button = new QPushButton(plant,this);
    //     // QString styleSheet = "QPushButton{border-image: url(:new/prefix1/ConeheadZombieshow.png) 0 0 0 0 stretch stretch}";
    //     QString imageName = plant;
    //     QString styleSheet = QString("QPushButton{border-image: url(:new/prefix1/%1.png) 0 0 0 0 stretch stretch;color:transparent}").arg(imageName);

    //     button->setStyleSheet(styleSheet);
    //     button->setFixedSize(60, 80); // 设置固定大小
    //     bottomButtons.append(button);
    //     bottomLayout->addWidget(button);
    //     connect(button, &QPushButton::clicked, this, &PlantSelectionWidget::onPlantButtonClicked);
    // }
    // mainLayout->addLayout(bottomLayout);



    // 下面是可以选择的植物 - 添加背景图片和布局
    QWidget *bottomContainer = new QWidget(this);
    bottomContainer->setFixedSize(590, 570); // 5行按钮，每行8个，加上间距
    bottomContainer->setStyleSheet("border-image: url(:/new/prefix1/PanelBackground.png) 0 0 0 0 stretch stretch;"
                                   "background-repeat: no-repeat;"
                                   "background-position: center;");

    // 使用绝对定位排列按钮，每行8个，共5行
    const int buttonsPerRow = 8;
    const int maxRows = 5;
    const int buttonWidth = 60;
    const int buttonHeight = 80;
    const int horizontalSpacing = 5; // 水平间距
    const int verticalSpacing = 5;   // 垂直间距
    const int startX = 35;           // 起始X坐标
    const int startY = 40;           // 起始Y坐标

    // 计算实际需要的行数
    int rowsNeeded = (allPlants.size() + buttonsPerRow - 1) / buttonsPerRow;
    rowsNeeded = qMin(rowsNeeded, maxRows); // 最多5行

    for (int i = 0; i < allPlants.size() && i < buttonsPerRow * maxRows; ++i) {
        const QString& plant = allPlants[i];
        QPushButton *button = new QPushButton(plant, bottomContainer);

        // 设置按钮样式和图片
        QString imageName = plant;
        QString styleSheet = QString("QPushButton{border-image: url(:new/prefix1/%1.png) 0 0 0 0 stretch stretch;color:transparent}").arg(imageName);
        button->setStyleSheet(styleSheet);
        button->setFixedSize(buttonWidth, buttonHeight);

        // 计算按钮位置
        int row = i / buttonsPerRow;
        int col = i % buttonsPerRow;

        int xPos = startX + col * (buttonWidth + horizontalSpacing);
        int yPos = startY + row * (buttonHeight + verticalSpacing);

        button->move(xPos, yPos);

        bottomButtons.append(button);
        connect(button, &QPushButton::clicked, this, &PlantSelectionWidget::onPlantButtonClicked);
    }

    mainLayout->addWidget(bottomContainer);



    // 状态标签
    statusLabel = new QLabel("请选择1-7种植物", this);
    mainLayout->addWidget(statusLabel);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &PlantSelectionWidget::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &PlantSelectionWidget::onCancelButtonClicked);

    setLayout(mainLayout);
    setWindowTitle("选择植物");
}

QVector<QString> PlantSelectionWidget::getSelectedPlants() const
{
    return selectedPlants;
}

void PlantSelectionWidget::onPlantButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    if (bottomButtons.contains(clickedButton)) {
        // 点击下面的植物，尝试添加到上面
        for (int i = 0; i < topButtons.size(); ++i) {
            if (topButtons[i]->text().isEmpty()) {
                topButtons[i]->setText(clickedButton->text());
                QString imageName =clickedButton->text();
                QString styleSheet = QString("QPushButton{border-image: url(:new/prefix1/%1.png) 0 0 0 0 stretch stretch;color:transparent}").arg(imageName);
                topButtons[i]->setStyleSheet(styleSheet);
                // clickedButton->setVisible(false);
                QString grayedStyle = QString(
                                          "QPushButton{"
                                          "    border-image: url(:new/prefix1/%1.png) 0 0 0 0 stretch stretch;"
                                          "    color: transparent;"
                                          "    background-color: rgba(128, 128, 128, 128);"  // 半透明灰色
                                          "}"
                                          ).arg(clickedButton->text());

                clickedButton->setStyleSheet(grayedStyle);
                clickedButton->setEnabled(false);

                selectedPlants.append(clickedButton->text());
                statusLabel->setText(QString("已选择 %1/7 种植物").arg(selectedPlants.size()));
                break;
            }
        }
    } else if (topButtons.contains(clickedButton)) {
        // 点击上面的植物，回退到下面
        if (!clickedButton->text().isEmpty()) {
            for (QPushButton *button : bottomButtons) {
                if (button->text() == clickedButton->text()) {
                    // button->setVisible(true);
                    QString styleSheet = QString("QPushButton{border-image: url(:new/prefix1/%1.png) 0 0 0 0 stretch stretch;color:transparent}").arg(button->text());
                    button->setStyleSheet(styleSheet);
                    button->setEnabled(true);
                    break;
                }
            }
            selectedPlants.removeOne(clickedButton->text());
            clickedButton->setText("");
            clickedButton->setStyleSheet("border: 1px solid gray;"
                                         "border-image:none;" // 半透明背景
                                         "border-radius: 5px;");
            statusLabel->setText(QString("已选择 %1/7 种植物").arg(selectedPlants.size()));
        }
    }
}

void PlantSelectionWidget::onOkButtonClicked()
{
    if (selectedPlants.isEmpty()) {
        statusLabel->setText("至少选择一种植物!");
        return;
    }

    accept(); // 关闭对话框并返回Accepted状态
}

void PlantSelectionWidget::onCancelButtonClicked()
{
    reject(); // 关闭对话框并返回Rejected状态
}
