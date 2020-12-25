#include <qmath.h>

#include "Headers/DialogueHandler.h"
#include "Headers/DialogueTriggerBox.h"
#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Projectile.h"
#include "Headers/Tile.h"

extern Game *game;

PlayerCharacter::PlayerCharacter()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));

    gunArm = new GunArm();
    aimDirection = AimDirection::aimingRight;
    shoulderPosition = pos() + QPointF(35, 60);
    gunArm->setPos(shoulderPosition);

    projectilesound = new QMediaPlayer();
    projectilesound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/projectile.mp3"));
}

PlayerCharacter::~PlayerCharacter()
{
    qDebug() << "delete player";
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
        // TODO - popraviti pozicije za 3. i 5. nivo
        if(this->x() < 450)
            pauseScreen->setPos(300, scene()->sceneRect().center().y() - 180);
        else
            pauseScreen->setPos(this->x() - 200, scene()->sceneRect().center().y() - 180);
        game->currentLevel->addItem(pauseScreen);
    }
    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && isPaused){
        isPaused = false;
        game->currentLevel->removeItem(pauseScreen);
        delete pauseScreen;
    }

    if(event->key() == Qt::Key_Escape)
    {
        exit(0);
    }

    if(event->key() == Qt::Key_R && game->getIsGameOver() == true)
    {
        //game->currentLevel->removeItem(game->gameOverScreen);
        //delete game->gameOverScreen;
        game->getGameOverLabel()->hide();
        health = 8;
        emit healthChanged();
        game->levelID--;
        game->changeLevel();
    }


    if(event->key() == Qt::Key_D)
    {
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));
        }
        canMove = true;
        velocityX = 11;
    }
    else if(event->key() == Qt::Key_A)
    {
        if (game->getLevelID() == 2)
        {
           setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_left.png"));
        }
        canMove = true;
        velocityX = -11;
    }
    else if(event->key() == Qt::Key_Space && isOnGround)
    {
        velocityY = -14;
        setPos(x(), y() + velocityY);
        isOnGround = false;
    }
}

void PlayerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        velocityX = 0;
        canMove = false;
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
    else if(event->key() == Qt::Key_A)
    {
        velocityX = 0;
        canMove = false;
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
}

void PlayerCharacter::advance(int step)
{
    if(canMove){
        walk();
    }
    jump();
    detectCollision();
}

void PlayerCharacter::aimAtPoint(QPoint point)
{
    targetPoint = game->mapToScene(point);

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

void PlayerCharacter::shootProjectile()
{
    Projectile *projectile = new Projectile(Projectile::Player);

    QLineF ln(shoulderPosition, targetPoint );
    qreal angle = -1 * ln.angle();
    qreal dy = 80 * qSin(qDegreesToRadians(angle));
    qreal dx = 80 * qCos(qDegreesToRadians(angle));

    projectileStartPoint = QPointF(shoulderPosition + QPointF(dx, dy));
    projectile->setPos(projectileStartPoint.x(), projectileStartPoint.y());
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

void PlayerCharacter::increaseHealth()
{
    if (health < 8)
        health++;
}

void PlayerCharacter::decreaseHealth()
{
    if (health > 0)
        health--;
    else if (health == 0)
        emit playerIsDead();
}

//----------------GETERI/SETERI-------------------

GunArm *PlayerCharacter::getGunArm() const
{
    return gunArm;
}

int PlayerCharacter::getHealth() const
{
    return health;
}

//----------------SLOTOVI-------------------

void PlayerCharacter::jump()
{
    if(!isOnGround)
    {
        if(y() < 0) // udara gore
        {
            setPos(x(), 0);
            velocityY = 5;
        }
        setPos(x(), y() + velocityY);

        if(velocityY < 10)
            velocityY += gravity;
    }

    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

    game->centerOn(this);
}

void PlayerCharacter::walk()
{
    // ako Player pokusa da ode van ekrana
    if (x() > game->currentLevel->width() - 3 * 45) // desno
    {
        setPos(game->currentLevel->width() - 3 * 45, y());
    }
    else if(x() < 0) // levo
    {
        setPos(0, y());
    }

    setPos(x() + velocityX, y());

    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

    game->centerOn(this);
}

void PlayerCharacter::detectCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    if(colliding_items.size())
    {
        for (int i = 0, n = colliding_items.size(); i < n; i++)
        {
            if (typeid(*(colliding_items[i])) == typeid(DialogueTriggerBox))
            {
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
                emit startDialogue();
            }
            if (typeid(*(colliding_items[i])) == typeid(Pickup))
            {
                increaseHealth();
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
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

                if(playerRectPoints[2].y() <= tileRectPoints[0].y() + 10)
                {
                    isOnGround = true;
                    //qDebug()<<"1";
                }
                else if(playerRectPoints[3].x() < tileRectPoints[3].x() - 25 && playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                    setPos(x() - 11, y());
                    //qDebug()<<"2"<<playerRectPoints;
                }
                else if(playerRectPoints[2].x() >= tileRectPoints[2].x() && playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                     setPos(x() + 11, y());
                     //qDebug()<<"3";
                }
                if(playerRectPoints[1].y() <= tileRectPoints[3].y() + 10 && playerRectPoints[2].x() > tileRectPoints[3].x() + 2
                   && playerRectPoints[3].x() < tileRectPoints[2].x() - 2)
                {
                        velocityY = 5;
                        //qDebug()<<"4";
                }

                auto t = dynamic_cast<Tile*>(colliding_items[i]);
                if (t->getType() == '^' || t->getType() == 'W')
                {
                    emit playerIsDead();
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
