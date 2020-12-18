QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 \
          resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/Building.cpp \
    Source/Character.cpp \
    Source/DialogueBox.cpp \
    Source/DialogueHandler.cpp \
    Source/EnemyCharacter.cpp \
    Source/Game.cpp \
    Source/GunArm.cpp \
    Source/HealthBar.cpp \
    Source/Help.cpp \
    Source/Level.cpp \
    Source/Menu.cpp \
    Source/NPCharacter.cpp \
    Source/Options.cpp \
    Source/Pickup.cpp \
    Source/PlayerCharacter.cpp \
    Source/Portal.cpp \
    Source/Projectile.cpp \
    Source/Tile.cpp \
    Source/main.cpp

HEADERS += \
    Headers/Building.h \
    Headers/Character.h \
    Headers/DialogueBox.h \
    Headers/DialogueHandler.h \
    Headers/EnemyCharacter.h \
    Headers/Game.h \
    Headers/GunArm.h \
    Headers/HealthBar.h \
    Headers/Help.h \
    Headers/Level.h \
    Headers/Menu.h \
    Headers/NPCharacter.h \
    Headers/Options.h \
    Headers/Pickup.h \
    Headers/PlayerCharacter.h \
    Headers/Portal.h \
    Headers/Projectile.h \
    Headers/Tile.h

FORMS += \
    Forms/Game.ui \
    Forms/Help.ui \
    Forms/Menu.ui \
    Forms/Options.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
