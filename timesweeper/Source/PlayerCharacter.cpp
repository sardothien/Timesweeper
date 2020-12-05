#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Tile.h"
#include "Headers/Projectile.h"
#include <QGraphicsSceneMouseEvent>

#include <iostream>

extern Game *game;

PlayerCharacter::PlayerCharacter(Character *parent)
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));

    timerJump = new QTimer();
    connect(timerJump, &QTimer::timeout, this, &PlayerCharacter::jump);

    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &PlayerCharacter::walk);

    timerCollision = new QTimer();
    connect(timerCollision, &QTimer::timeout, this, &PlayerCharacter::detectCollision);

    isOnGround = true;
    timerJump->start(25);
    timerCollision->start(25);

    projectilesound = new QMediaPlayer();
    projectilesound->setMedia(QUrl("qrc:/Sounds/Resources/projectile.mp3"));
}

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_E && DialogueHandler::isDialogueActive)
    {
        DialogueHandler::advanceDialogue();
    }
    //NOTE: NE BRISITE KOD ISPOD DOK NE ZAVRSIM CELU IMPLEMENTACIJU DIJALOGA

    if(event->key() == Qt::Key_Q){  //test
        DialogueHandler::setDialogueActive(!DialogueHandler::isDialogueActive);
    }
    if(event->key() == Qt::Key_1){  //test
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_2){  //test
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_3){  //test
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_4){  //test
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_5){  //test
        DialogueHandler::initializeDialogue();
    }


    if(event->key() == Qt::Key_Right)
    {
        velocityX = 11;
        timerWalk->start(25);

    }
    else if(event->key() == Qt::Key_Left)
    {
        velocityX = -11;
        timerWalk->start(25);

    }
    else if(event->key() == Qt::Key_Space && isOnGround)
    {
        velocityY=-13;
        setPos(x(),y()+velocityY);
        isOnGround = false;
    }
}

void PlayerCharacter::shootProjectile()
{
    Projectile *projectile = new Projectile();
    projectile->setPos(x()+50,y()+70);
    scene()->addItem(projectile);

    if (projectilesound->state() == QMediaPlayer::PlayingState)
    {
       projectilesound->setPosition(0);
    }
    else if (projectilesound->state() == QMediaPlayer::StoppedState)
    {
        projectilesound->play();
    }
}

void PlayerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        timerWalk->stop();

    }
    else if(event->key() == Qt::Key_Left)
    {
        timerWalk->stop();
    }
    else if(event->key() == Qt::Key_X)
    {
        shootProjectile();
    }
}

void PlayerCharacter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        shootProjectile();
    }

    QGraphicsItem::mousePressEvent(event);
}

void PlayerCharacter::jump()
{
    if(!isOnGround)
    {
        //timerWalk->stop();
        setPos(x(),y()+velocityY);
        velocityY += gravity;
    }
    game->centerOn(this);
}

void PlayerCharacter::walk()
{
    setPos(x() + velocityX, y());
    if((game->currentLevelNpc->x() - x()) <= 200 &&  (game->currentLevelNpc->x() - x()) >= 190)
    {
        emit nearNPC();
    }

    game->centerOn(this);
}

void PlayerCharacter::detectCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    if(colliding_items.size())
    {
        for (int i = 0, n = colliding_items.size(); i < n; i++)
        {
            if (typeid(*(colliding_items[i])) == typeid(Pickup))
            {
                increaseHealth();
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
            else if(typeid(*(colliding_items[i])) == typeid(Tile))
            {
                isOnGround = true;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Portal) && (game->currentLevelPortal->x() - x()) < 30 && (game->currentLevelPortal->y() - y()) < 30)
            {
                game->currentLevel->removeItem(game->player);
                emit enteredPortal();
            }
      }
    }
    else
    {
        isOnGround = false;
    }
}

