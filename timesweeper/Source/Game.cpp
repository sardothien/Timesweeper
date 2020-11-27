#include <iostream>
#include <QWidget>
#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"
#include <QtMultimedia/QMediaPlayer>

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    int levelId = 1;

    //prologue level
    currentLevel = Level::LoadLevel(levelId);

    if(levelId == 1){
        currentLevel->setSceneRect(0, 0, 2300, 700);
        currentLevel->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_1_prologue.png")));
    }

    DialogueHandler::initializeDialogue( /*level id*/ 1);
    setScene(currentLevel);
    currentLevel->addItem(player);
    centerOn(player);

    // play background music
    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Sounds/Resources/bgsound.mp3"));
    music->play();

}
