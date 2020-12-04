#include <iostream>
#include <QtMultimedia/QMediaPlayer>
#include <QWidget>
#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"

int Game::levelID;

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    levelID = 3;

    //prologue level
    currentLevel = Level::LoadLevel();

    if(levelID == 1){
        currentLevel->setSceneRect(0, 0, 2300, 700);
        currentLevel->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_1_prologue.png")));
    }
    else if(levelID == 2){ // u ostalim nivoima igrac je nizi
        player->setScale(0.8);
        currentLevel->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_2_maya.png")));
    }
    else if(levelID == 3){
        currentLevel->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_3_wild_west.png")));
    }

    DialogueHandler::initializeDialogue();
    setScene(currentLevel);
    currentLevel->addItem(player);
    centerOn(player);

    // play background music
    QMediaPlayer *music = new QMediaPlayer();
    if(levelID == 1)
    {
        music->setMedia(QUrl("qrc:/Sounds/Resources/bgsound_level_1.mp3"));
        music->play();
    }
    else if(levelID == 3)
    {
        music->setMedia(QUrl("qrc:/Sounds/Resources/bgsound_level_3.mp3"));
        music->play();
    }

}
