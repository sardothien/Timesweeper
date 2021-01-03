cmake_minimum_required(VERSION 3.16)
project(timesweeper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(QT_USE_QTMULTIMEDIA TRUE)
set(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

set(RESOURCES
    resources.qrc
)

qt5_add_big_resources(RES_SOURCES ${RESOURCES})

set(SOURCES
    Source/main.cpp
    Source/Building.cpp
    Source/Character.cpp
    Source/DialogueBox.cpp
    Source/DialogueHandler.cpp
    Source/DialogueTriggerBox.cpp
    Source/EnemyBoss.cpp
    Source/EnemyCharacter.cpp
    Source/EnemyHealthBar.cpp
    Source/Game.cpp
    Source/GunArm.cpp
    Source/Help.cpp
    Source/Level.cpp
    Source/Menu.cpp
    Source/Options.cpp
    Source/Pickup.cpp
    Source/PlayerCharacter.cpp
    Source/Portal.cpp
    Source/Projectile.cpp
    Source/Tile.cpp
)

set(HEADERS
    Headers/Building.h
    Headers/Character.h
    Headers/DialogueBox.h
    Headers/DialogueHandler.h
    Headers/DialogueTriggerBox.h
    Headers/EnemyBoss.h
    Headers/EnemyCharacter.h
    Headers/EnemyHealthBar.h
    Headers/Game.h
    Headers/GunArm.h
    Headers/Help.h
    Headers/Level.h
    Headers/Menu.h
    Headers/Options.h
    Headers/Pickup.h
    Headers/PlayerCharacter.h
    Headers/Portal.h
    Headers/Projectile.h
    Headers/Tile.h
)

set(UIS
    Forms/Game.ui
    Forms/Help.ui
    Forms/Menu.ui
    Forms/Options.ui
)

qt5_wrap_ui(UI_HEADERS ${UIS})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${UI_HEADERS} ${RES_SOURCES})
qt5_use_modules(${PROJECT_NAME} Core Gui Multimedia Widgets MultimediaWidgets)
