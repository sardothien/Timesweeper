#include <QDebug>

#include <iostream>
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

    connect(player, &PlayerCharacter::enteredPortal, this, &Game::changeLevel);
    connect(player, &PlayerCharacter::nearNPC, this, &Game::triggerDialogue);

    music = new QMediaPlayer();

    //NOTE: menjanje nivoa trenutno radi pravilno samo ako ovde prvo stoji levelID = 1, (nisam nasao zasto)
    //ako krenete odmah od vasih nivoa, desice se da chrashuje kada pokusate da se pomerite levo/desno
    //Mina, u tvoj nivo sam privremeno dodao neki portal pri pocetku da bi Igor mogao da udje u svoj nivo dok ne popravimo ovaj bag
    levelID = 1;
    changeLevel();

}

void Game::changeLevel()
{
    //qDebug() << "signal caught changeLevel!";
    currentLevel = Level::LoadLevel();
    DialogueHandler::initializeDialogue();
    setScene(currentLevel);
    player->setFocus();
    player->setPos(60, 400);
    if(levelID != 1)
    {
        player->setScale(0.8);
    }
    currentLevel->addItem(player);
    centerOn(player);
    playMusic();
    levelID++;
}

void Game::triggerDialogue()
{
    //qDebug() << "signal caught triggerDialogue";
    DialogueHandler::setDialogueActive(true);
    DialogueHandler::advanceDialogue();
}

void Game::playMusic()
{
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

Portal *Game::getCurrentLevelPortal()
{
    return currentLevelPortal;
}

void Game::setCurrentLevelPortal(Portal *portal)
{
    currentLevelPortal = portal;
}

NPCharacter *Game::getCurrentLevelNpc()
{
    return currentLevelNpc;
}

void Game::setCurrentLevelNpc(NPCharacter *npc)
{
    currentLevelNpc = npc;
}
