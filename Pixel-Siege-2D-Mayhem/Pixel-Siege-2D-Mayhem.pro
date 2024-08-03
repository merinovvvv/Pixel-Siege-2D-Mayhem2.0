QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authowindow.cpp \
    game.cpp \
    gameplaywindow.cpp \
    ghost.cpp \
    hero.cpp \
    loginwindow.cpp \
    main.cpp \
    main_menu.cpp \
    mapchoosewindow.cpp \
    monster.cpp \
    pause.cpp \
    scaryghost.cpp \
    skeleton.cpp \
    slime.cpp \
    statswindow.cpp \
    wolf.cpp

HEADERS += \
    authowindow.h \
    game.h \
    gameplaywindow.h \
    ghost.h \
    hero.h \
    json.hpp \
    json_fwd.hpp \
    loginwindow.h \
    main_menu.h \
    mapchoosewindow.h \
    monster.h \
    pause.h \
    scaryghost.h \
    skeleton.h \
    slime.h \
    statswindow.h \
    wolf.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
