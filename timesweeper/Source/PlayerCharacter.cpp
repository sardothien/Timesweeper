#include <QDebug>

#include <QGraphicsScene>
#include <iostream>
#include <QKeyEvent>
#include <QList>

#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Tile.h"
#include "Headers/Projectile.h"

#include <QGraphicsLineItem>

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
    projectilesound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/projectile.mp3"));
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


    if(event->key() == Qt::Key_D)
    {
        if (game->getLevelID() != 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        }
        else
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));
        }

        velocityX = 11;
        timerWalk->start(25);

    }
    else if(event->key() == Qt::Key_A)
    {
        //qDebug() << "levelID je: " << game->getLevelID();
        if (game->getLevelID() != 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_left.png"));
        }
        else
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_left.png"));
        }

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
    projectile->setPos(x()+80, y()+70);

    QLineF ln(projectile->pos(), targetPoint );
    //debug linija ciljanja
    //game->currentLevel->addItem(new QGraphicsLineItem(ln));
    qreal angle = -1 * ln.angle();

    projectile->setRotation(angle);

    game->currentLevel->addItem(projectile);

    if (projectilesound->state() == QMediaPlayer::PlayingState)
    {
       projectilesound->setPosition(0);
       projectilesound->play();
    }
    else if (projectilesound->state() == QMediaPlayer::StoppedState)
    {
        projectilesound->play();
    }
}

void PlayerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        timerWalk->stop();

        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
    else if(event->key() == Qt::Key_A)
    {
        timerWalk->stop();

        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
}

void PlayerCharacter::jump()
{
    if(!isOnGround)
    {
        //timerWalk->stop();
        if(y() < 0) // udara gore
        {
            setPos(x(), 0);
        }
        setPos(x(),y()+velocityY);
        velocityY += gravity;
    }
    game->centerOn(this);
}

void PlayerCharacter::walk()
{
    // ako Player pokusa da ode van ekrana
    if (x() > game->currentLevel->width()-3*45) // desno
    {
        setPos(game->currentLevel->width()-3*45, y());
    }
    else if(x() < 0) // levo
    {
        setPos(0, y());
    }

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
            else if(typeid(*(colliding_items[i])) == typeid(Projectile)){
                // TODO: decreaseHealth()
                // NOTE: trenutno Player ima koliziju sa Projectile kad puca
                // (samo promeniti poziciju Projectile-a)
                // qDebug() << "Player hit!";
            }
      }
    }
    else
    {
        isOnGround = false;
    }
}

void PlayerCharacter::aimAtPoint(QPoint point)
{
    //qDebug() << "trarget:" << targetPoint;
    //NOTE: pitati asistenta za pomoc ovde! Ako umesto if-ova imamo samo targetPoint = point, ponasanje nije ispravno
    //otkomentarisi liniju 114 (dodavanje linije na scenu) za testiranje
    if(x() >= 500)
    {
        targetPoint.setX(point.x() + x() - 500);
        targetPoint.setY(point.y());
    }
    else
    {
        targetPoint = point;
    }
}
