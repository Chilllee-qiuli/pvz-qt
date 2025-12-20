QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basiczombie.cpp \
    bgmmanager.cpp \
    card.cpp \
    cherry.cpp \
    chilipepper.cpp \
    chomper.cpp \
    flagzombie.cpp \
    flameeffect.cpp \
    flow_layout.cpp \
    game.cpp \
    loading.cpp \
    main.cpp \
    Mainwindow.cpp \
    map.cpp \
    other.cpp \
    pea.cpp \
    peashot.cpp \
    plant.cpp \
    plant_book_dialog.cpp \
    plant_card_widget.cpp \
    plant_registry.cpp \
    plantselectionwidget.cpp \
    plantshow.cpp \
    potato.cpp \
    repeater.cpp \
    shop.cpp \
    shovel.cpp \
    snowpea.cpp \
    startpage.cpp \
    sun.cpp \
    sunflower.cpp \
    thorn.cpp \
    wallnut.cpp \
    zombie.cpp \
    mower.cpp \
    bucketzombie.cpp \
    conezombie.cpp \
    footballzombie.cpp \
    screenzombie.cpp \
    zombie_book_dialog.cpp \
    zombie_card_widget.cpp \
    zombie_registry.cpp \
    zombieshow.cpp \
    pausebutton.cpp

HEADERS += \
    Mainwindow.h \
    basiczombie.h \
    bgmmanager.h \
    card.h \
    cherry.h \
    chilipepper.h \
    chomper.h \
    flagzombie.h \
    flameeffect.h \
    flow_layout.h \
    game.h \
    loading.h \
    map.h \
    other.h \
    pea.h \
    peashot.h \
    plant.h \
    plant_book.qss \
    plant_book_dialog.h \
    plant_card_widget.h \
    plant_registry.h \
    plantselectionwidget.h \
    plantshow.h \
    potato.h \
    repeater.h \
    shop.h \
    shovel.h \
    snowpea.h \
    startpage.h \
    sun.h \
    sunflower.h \
    thorn.h \
    wallnut.h \
    zombie.h \
    mower.h \
    bucketzombie.h \
    conezombie.h \
    footballzombie.h \
    screenzombie.h \
    zombie_book_dialog.h \
    zombie_card_widget.h \
    zombie_registry.h \
    zombieshow.h \
    pausebutton.h

FORMS += \
    Mainwindow.ui \
    plantshow.ui \
    zombieshow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/imges.qrc \
    resources.qrc \
    sound/sound.qrc
     # resources.qrc # 确保包含资源文件

DISTFILES += \
    zombie_book.qss
