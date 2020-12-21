#include <QDebug>

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QStyle>

#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"
#include "ui_Game.h"

int Game::levelID;

void Game::setHealthBar()
{
    QString health;
    for (int i = 1; i <= 8; i++)
    {
        health = QString::number(i);
        health = "hb" + health;

        if (player->getHealth() == i)
            label->setProperty("foo", health);
    }

    label->style()->unpolish(label);
    label->style()->polish(label);
    label->update();
}

bool Game::getSoundOn() const
{
    return soundOn;
}

void Game::setSoundOn(bool value)
{
    soundOn = value;
}



Game::Game(QWidget *parent)
{
    ui->setupUi(this);
    setWindowTitle("timesweeper");

    label = new QLabel(this);
    label->setGeometry(10,10,155,55);
    label->setProperty("foo", "hb8");

    setMouseTracking(true);

    cursor = QCursor(QPixmap(":/Other/Resources/Other/crosshair.png"), 25 , 25);
    setCursor(cursor);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    projectileTimer = new QTimer(this);
    projectileTimer->start(50);

    enemyWalkTimer = new QTimer(this);
    enemyWalkTimer->start(15);

    enemyShootTimer = new QTimer(this);
    enemyShootTimer->start(1000);

    tileMoveTimer = new QTimer(this);
    tileMoveTimer->start(10);

    connect(player, &PlayerCharacter::enteredPortal, this, &Game::changeLevel);
    connect(player, &PlayerCharacter::nearNPC, this, &Game::triggerDialogue);
    connect(player, &PlayerCharacter::healthChanged, this, &Game::setHealthBar);

    music = new QMediaPlayer();

    //NOTE: menjanje nivoa trenutno radi pravilno samo ako ovde prvo stoji levelID = 1, (nisam nasao zasto)
    //ako krenete odmah od vasih nivoa, desice se da chrashuje kada pokusate da se pomerite levo/desno
    //Mina, u tvoj nivo sam privremeno dodao neki portal pri pocetku da bi Igor mogao da udje u svoj nivo dok ne popravimo ovaj bag
    levelID = 1;
    changeLevel();
}

QTimer *Game::getTileMoveTimer() const
{
    return tileMoveTimer;
}

QTimer *Game::getEnemyShootTimer() const
{
    return enemyShootTimer;
}

QTimer *Game::getEnemyWalkTimer() const
{
    return enemyWalkTimer;
}

QTimer *Game::getProjectileTimer() const
{
    return projectileTimer;
}

int Game::getLevelID()
{
    return levelID;
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->pos();
    player->aimAtPoint(event->pos());
    player->setFocus();
}

void Game::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->pos();
    if((event->button() == Qt::LeftButton) && (levelID - 1 != 1))
    {
        player->shootProjectile();
    }
    player->setFocus();
}

void Game::changeLevel()
{
    //qDebug() << "signal caught changeLevel!";
    currentLevel = Level::LoadLevel();
    DialogueHandler::initializeDialogue();
    setScene(currentLevel);
    player->setFocus();
    player->setPos(currentLevelPlayerStartPosition);

    if(levelID != 1)
    {
        player->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        player->setScale(0.8);
    }
    currentLevel->addItem(player);
    //NOTE: ovaj if ne sme da se spoji sa ovim iznad jer se pixmap igraca iscrta iznad pixmapa puske
    if(levelID != 1)
    {
        currentLevel->addItem(player->getGunArm());

    }
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
        music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_1.mp3"));
    }
    else if(levelID == 2)
    {
        music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_2.mp3"));
    }
    else if(levelID == 3)
    {
        //music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_3.mp3"));
    }
    else if(levelID == 4)
    {
        music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_4.mp3"));
    }
    else if(levelID == 5)
    {
    }

    if(soundOn && levelID != 1)
        music->play();
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
