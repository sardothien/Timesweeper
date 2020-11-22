QT       += core gui \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/Character.cpp \
    Source/EnemyCharacter.cpp \
    Source/Game.cpp \
    Source/Level.cpp \
    Source/NPCharacter.cpp \
    Source/Pickup.cpp \
    Source/PlayerCharacter.cpp \
    Source/Tile.cpp \
    Source/main.cpp

HEADERS += \
    Headers/Character.h \
    Headers/EnemyCharacter.h \
    Headers/Game.h \
    Headers/Level.h \
    Headers/NPCharacter.h \
    Headers/Pickup.h \
    Headers/PlayerCharacter.h \
    Headers/Tile.h

FORMS += \
    Forms/TimesweeperMainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
