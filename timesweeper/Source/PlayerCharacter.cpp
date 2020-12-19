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

#include "Headers/GunArm.h"
#include <QGraphicsRectItem>

#include <qmath.h>

extern Game *game;

PlayerCharacter::PlayerCharacter(Character *parent)
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));

    gunArm = new GunArm();
    aimDirection = AimDirection::aimingRight;
    shoulderPosition = pos() + QPointF(35, 60);
    gunArm->setPos(shoulderPosition);

    timerJump = new QTimer();
    connect(timerJump, &QTimer::timeout, this, &PlayerCharacter::jump);

    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &PlayerCharacter::walk);

    timerCollision = new QTimer();
    connect(timerCollision, &QTimer::timeout, this, &PlayerCharacter::detectCollision);

    isOnGround = true;
    timerJump->start(15);
    timerCollision->start(10);

    projectilesound = new QMediaPlayer();
    projectilesound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/projectile.mp3"));
}

int PlayerCharacter::getHealth() const
{
    return health;
}

void PlayerCharacter::increaseHealth()
{
    if (health < 8)
        health++;
}

void PlayerCharacter::decreaseHealth()
{
    if (health > 0)
        health--;
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

    // TODO - stvarno pauzirati igru (ovo je samo iscrtavanje pause slike)
    // NOTE - prebaciti u Game klasu
    if(event->key() == Qt::Key_P && !isPaused){
        isPaused = true;
        pauseScreen = new QGraphicsPixmapItem;
        pauseScreen->setPixmap(QPixmap(":/Other/Resources/Other/pause.png"));
        pauseScreen->setOpacity(0.9);
        if(this->x() < 450)
            pauseScreen->setPos(300, scene()->sceneRect().center().y()-180);
        else
            pauseScreen->setPos(this->x()-200, scene()->sceneRect().center().y()-180);
        game->currentLevel->addItem(pauseScreen);
    }
    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && isPaused){
        isPaused = false;
        game->currentLevel->removeItem(pauseScreen);
        delete pauseScreen;
    }
    if(event->key() == Qt::Key_Escape){
        exit(0);
    }


    if(event->key() == Qt::Key_D)
    {
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));
        }
        velocityX = 11;
        timerWalk->start(25);
    }
    else if(event->key() == Qt::Key_A)
    {
        //qDebug() << "levelID je: " << game->getLevelID();
        if (game->getLevelID() == 2)
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
    QLineF ln(shoulderPosition, targetPoint );
    //debug linija ciljanja
    //game->currentLevel->addItem(new QGraphicsLineItem(ln));
    qreal angle = -1 * ln.angle();

    qreal dy = 80 * qSin(qDegreesToRadians(angle));
    qreal dx = 80 * qCos(qDegreesToRadians(angle));

    //potreban nam je dodatni offset od 63px ako igrac cilja na levo, jer smo tretirali da je shoulderPosition
    //u tom slucaju 17 umesto 80, da nebi bilo treperenja
    if(aimDirection == AimDirection::aimingLeft)
    {
        dx += 63;
    }
    projectileStartPoint = QPointF(shoulderPosition + QPointF(dx, dy));
    projectile->setPos(projectileStartPoint.x(), projectileStartPoint.y());

    QLineF ln1(projectileStartPoint, targetPoint );
    //game->currentLevel->addItem(new QGraphicsLineItem(ln1));

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
        if(y() < 0) // udara gore
        {
            setPos(x(), 0);
            velocityY = 5;
        }
        setPos(x(),y()+velocityY);

        if(velocityY<10)
            velocityY += gravity;
    }

    //gunArm->setPos(pos() + QPoint(35, 60));
    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

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

    //gunArm->setPos(pos() + QPoint(35, 60));
    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

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
                emit healthChanged();
            }
            else if(typeid(*(colliding_items[i])) == typeid(Projectile))
            {
                decreaseHealth();
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
                emit healthChanged();

            }
            else if(typeid(*(colliding_items[i])) == typeid(Tile))
            {
                QRectF tileRect = colliding_items[i]->boundingRect();
                QPolygonF tileRectPoints = colliding_items[i]->mapToScene(tileRect);

                playerRectPoints = mapToScene(boundingRect());

                if(playerRectPoints[2].y() <= tileRectPoints[0].y()+10)
                {
                    isOnGround = true;
                    //qDebug()<<"1";
                }else if(playerRectPoints[3].x() < tileRectPoints[3].x()-25 && playerRectPoints[1].y() <= tileRectPoints[3].y()-20)
                {
                            timerWalk->stop();
                            setPos(x()-11,y());
                            qDebug()<<"2"<<playerRectPoints;
                }else if(playerRectPoints[2].x() >= tileRectPoints[2].x() && playerRectPoints[1].y() <= tileRectPoints[3].y()-20)
                {
                            timerWalk->stop();
                            setPos(x()+11 ,y());
                            qDebug()<<"3";
                }
                if(playerRectPoints[1].y() <= tileRectPoints[3].y()+10 && playerRectPoints[2].x() > tileRectPoints[3].x()+2 && playerRectPoints[3].x() < tileRectPoints[2].x()-2){
                        velocityY = 5;
                        //qDebug()<<"4";
                }

            }
            else if (typeid(*(colliding_items[i])) == typeid(Portal) && (game->currentLevelPortal->x() - x()) < 30 && (game->currentLevelPortal->y() - y()) < 30)
            {
                game->currentLevel->removeItem(game->player);
                emit enteredPortal();
            }
            else if(typeid(*(colliding_items[i])) == typeid(GunArm))
            {
                isOnGround = false;
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
    QLineF ln(shoulderPosition, targetPoint );
    qreal angle = -1 * ln.angle();

    if ( angle > -90 || angle < -270){
        aimDirection = AimDirection::aimingRight;
        gunArm->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_right.png"));
        gunArm->setTransformOriginPoint(6, 0);
        if(game->getLevelID() != 2 )
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        }
        gunArm->setRotation(angle);
    }
    else
    {
        aimDirection = AimDirection::aimingLeft;
        gunArm->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_left.png"));
        gunArm->setTransformOriginPoint(gunArm->boundingRect().width() - 6, 0);
        if(game->getLevelID() != 2 )
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_left.png"));
        }
        gunArm->setRotation(180 + angle);
    }

    //qDebug() << "trarget:" << targetPoint;
    //NOTE: pitati asistenta za pomoc ovde! Ako umesto if-ova imamo samo targetPoint = point, ponasanje nije ispravno
    //otkomentarisi liniju 114 (dodavanje linije na scenu) za testiranje
    if(x() >= 500)
    {
        targetPoint.setX(point.x() + x() - 500);
        targetPoint.setY(point.y());
    }

//    if(y() >= 500)
//    {
//        targetPoint.setY(point.y() + y() - 500);
//        //targetPoint.setX(point.x());
//    }

    else
    {
        targetPoint = point;
    }
    /*auto tmp = mapToScene(point);
    targetPoint = QPoint(tmp.x(), tmp.y());
    qDebug() << shoulderPosition << tmp << targetPoint;*/
}

void PlayerCharacter::updateShoudlerPosition()
{
    if(aimDirection == AimDirection::aimingRight)
    {
        shoulderPosition = pos() + QPointF(35, 60);
    }
    else if(aimDirection == AimDirection::aimingLeft)
    {
        shoulderPosition = pos() + QPointF(17, 60);
    }
}

GunArm *PlayerCharacter::getGunArm() const
{
    return gunArm;
}
