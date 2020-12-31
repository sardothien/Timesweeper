#include "Headers/PlayerCharacter.h"
#include "Headers/DialogueHandler.h"
#include "Headers/DialogueTriggerBox.h"
#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/Projectile.h"
#include "Headers/Tile.h"

#include <qmath.h>

extern Game *game;

PlayerCharacter::PlayerCharacter()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));

    m_gunArm           = new GunArm();
    m_aimDirection     = AimDirection::aimingRight;
    m_shoulderPosition = pos() + QPointF(35, 60);
    m_gunArm->setPos(m_shoulderPosition);

    m_projectileSound = new QMediaPlayer();
    m_projectileSound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/projectile.mp3"));
}

PlayerCharacter::~PlayerCharacter()
{
    qDebug() << "delete player";
}

//----------------GETERI/SETERI-------------------

GunArm *PlayerCharacter::getGunArm() const { return m_gunArm; }

int PlayerCharacter::getHealth() const { return m_health; }

bool PlayerCharacter::getSoundEffectOn() const { return m_soundEffectOn; }

void PlayerCharacter::setSoundEffectOn(bool value) { m_soundEffectOn = value; }

//------------------------------------------------

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_E && DialogueHandler::isDialogueActive)
    {
        DialogueHandler::advanceDialogue();
    }
    //NOTE: NE BRISITE KOD ISPOD DOK NE ZAVRSIM CELU IMPLEMENTACIJU DIJALOGA

    if(event->key() == Qt::Key_Q) // test
    {
        DialogueHandler::setDialogueActive(!DialogueHandler::isDialogueActive);
    }
    if(event->key() == Qt::Key_1) // test
    {
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_2) // test
    {
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_3) // test
    {
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_4) // test
    {
        DialogueHandler::initializeDialogue();
    }
    if(event->key() == Qt::Key_5) // test
    {
        DialogueHandler::initializeDialogue();
    }

    // TODO - stvarno pauzirati igru (ovo je samo iscrtavanje pause slike)
    if(event->key() == Qt::Key_P && !m_isPaused)
    {
        game->m_mainTimer->stop();
        m_isPaused = true;
        game->getPauseLabel()->show();
    }
    else if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && m_isPaused)
    {
        game->m_mainTimer->start(16);
        m_isPaused = false;
        game->getPauseLabel()->hide();
    }
    else if(event->key() == Qt::Key_R && game->getIsGameOver() == true)
    {
        game->getGameOverLabel()->hide();
        m_health = 8;
        emit healthChanged();
        game->m_levelID--;
        game->changeLevel();
    }

    if(event->key() == Qt::Key_D)
    {
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));
        }
        m_canMove   = true;
        m_velocityX = 5;
    }
    else if(event->key() == Qt::Key_A)
    {
        if (game->getLevelID() == 2)
        {
           setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_left.png"));
        }
        m_canMove   = true;
        m_velocityX = -5;
    }
    else if(event->key() == Qt::Key_Space && m_isOnGround)
    {
        m_velocityY = -14;
        setPos(x(), y() + m_velocityY);
        m_isOnGround = false;
    }

    if(event->key() == Qt::Key_Escape)
    {
        exit(0);
    }
}

void PlayerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_D)
    {
        m_velocityX = 0;
        m_canMove   = false;
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
    else if(event->key() == Qt::Key_A)
    {
        m_velocityX = 0;
        m_canMove   = false;
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_front.png"));
        }
    }
}

void PlayerCharacter::aimAtPoint(QPoint point)
{
    m_targetPoint = game->mapToScene(point);

    QLineF ln(m_shoulderPosition, m_targetPoint );
    qreal angle = -1 * ln.angle();

    if(angle > -90 || angle < -270)
    {
        m_aimDirection = AimDirection::aimingRight;
        m_gunArm->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_right.png"));
        m_gunArm->setTransformOriginPoint(6, 0);
        if(game->getLevelID() != 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        }
        m_gunArm->setRotation(angle);
    }
    else
    {
        m_aimDirection = AimDirection::aimingLeft;
        m_gunArm->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_left.png"));
        m_gunArm->setTransformOriginPoint(m_gunArm->boundingRect().width() - 6, 0);
        if(game->getLevelID() != 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_left.png"));
        }
        m_gunArm->setRotation(180 + angle);
    }
}

void PlayerCharacter::updateShoudlerPosition()
{
    if(m_aimDirection == AimDirection::aimingRight)
    {
        m_shoulderPosition = pos() + QPointF(35, 60);
    }
    else if(m_aimDirection == AimDirection::aimingLeft)
    {
        m_shoulderPosition = pos() + QPointF(17, 60);
    }
}

void PlayerCharacter::shootProjectile()
{
    auto *projectile = new Projectile(Projectile::Player);

    QLineF ln(m_shoulderPosition, m_targetPoint);
    qreal angle = -1 * ln.angle();
    qreal dy    = 80 * qSin(qDegreesToRadians(angle));
    qreal dx    = 80 * qCos(qDegreesToRadians(angle));

    m_projectileStartPoint = QPointF(m_shoulderPosition + QPointF(dx, dy));
    projectile->setPos(m_projectileStartPoint.x(), m_projectileStartPoint.y());
    projectile->setRotation(angle);

    game->m_currentLevel->addItem(projectile);

    if(m_projectileSound->state() == QMediaPlayer::PlayingState)
    {
       m_projectileSound->setPosition(0);
       if(m_soundEffectOn)
            m_projectileSound->play();
    }
    else if(m_projectileSound->state() == QMediaPlayer::StoppedState)
    {
        if(m_soundEffectOn)
            m_projectileSound->play();
    }
}

void PlayerCharacter::increaseHealth()
{
    if(m_health < 8)
    {
        m_health++;
    }
}

void PlayerCharacter::decreaseHealth()
{
    if(m_health > 0)
    {
        m_health--;
    }
    else if(m_health == 0)
    {
        emit playerIsDead();
    }
}

void PlayerCharacter::advance(int phase)
{
    QGraphicsItem::advance(phase);
    if(m_canMove)
    {
        walk();
    }
    jump();
    detectCollision();
}

void PlayerCharacter::jump()
{
    if(!m_isOnGround)
    {
        if(y() < 0) // udara gore
        {
            setPos(x(), 0);
            m_velocityY = 5;
        }

        setPos(x(), y() + m_velocityY);

        if(m_velocityY < 10)
            m_velocityY += m_gravity;
    }

    updateShoudlerPosition();
    m_gunArm->setPos(m_shoulderPosition);

    game->centerOn(this);
}

void PlayerCharacter::walk()
{
    // ako Player pokusa da ode van ekrana
    if(x() > game->m_currentLevel->width() - 3 * 45) // desno
    {
        setPos(game->m_currentLevel->width() - 3 * 45, y());
    }
    else if(x() < 0) // levo
    {
        setPos(0, y());
    }

    setPos(x() + m_velocityX, y());

    updateShoudlerPosition();
    m_gunArm->setPos(m_shoulderPosition);

    game->centerOn(this);
}

void PlayerCharacter::detectCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    if(colliding_items.size())
    {
        for(auto & colliding_item : colliding_items)
        {
            if(typeid(*(colliding_item)) == typeid(DialogueTriggerBox))
            {
                scene()->removeItem(colliding_item);
                //delete colliding_items[i];
                emit startDialogue();
            }
            if(typeid(*(colliding_item)) == typeid(Pickup))
            {
                increaseHealth();
                scene()->removeItem(colliding_item);
                //delete colliding_items[i];
                emit healthChanged();
            }
            else if(typeid(*(colliding_item)) == typeid(Projectile))
            {
                decreaseHealth();
                scene()->removeItem(colliding_item);
                delete colliding_item;
                emit healthChanged();
            }
            else if(typeid(*(colliding_item)) == typeid(Tile))
            {
                QRectF tileRect          = colliding_item->boundingRect();
                QPolygonF tileRectPoints = colliding_item->mapToScene(tileRect);

                m_playerRectPoints = mapToScene(boundingRect());

                if(m_playerRectPoints[2].y() <= tileRectPoints[0].y() + 10)
                {
                    m_isOnGround = true;
                    //qDebug()<<"1";
                }
                else if(m_playerRectPoints[3].x() < tileRectPoints[3].x() - 25 &&
                        m_playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                    setPos(x() - 11, y());
                    //qDebug()<<"2"<<playerRectPoints;
                }
                else if(m_playerRectPoints[2].x() >= tileRectPoints[2].x() &&
                        m_playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                    setPos(x() + 11, y());
                    //qDebug()<<"3";
                }
                if(m_playerRectPoints[1].y() <= tileRectPoints[3].y() + 10 &&
                   m_playerRectPoints[2].x() > tileRectPoints[3].x() + 2 &&
                   m_playerRectPoints[3].x() < tileRectPoints[2].x() - 2)
                {
                    m_velocityY = 5;
                    //qDebug()<<"4";
                }

                auto t = dynamic_cast<Tile*>(colliding_item);
                if(t->getType() == '^' || t->getType() == 'W')
                {
                    emit playerIsDead();
                }
            }
            else if(typeid(*(colliding_item)) == typeid(Portal) &&
                   (game->m_currentLevelPortal->x() - x()) < 30 &&
                   (game->m_currentLevelPortal->y() - y()) < 30)
            {
                game->m_currentLevel->removeItem(game->m_player);
                emit enteredPortal();
            }
            else if(typeid(*(colliding_item)) == typeid(GunArm))
            {
                m_isOnGround = false;
            }
        }
    }
    else
    {
        m_isOnGround = false;
    }
}
