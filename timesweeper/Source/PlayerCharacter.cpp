#include "Headers/PlayerCharacter.h"
#include "Headers/DialogueHandler.h"
#include "Headers/DialogueTriggerBox.h"
#include "Headers/Game.h"
#include "Headers/Help.h"
#include "Headers/Menu.h"
#include "Headers/Options.h"
#include "Headers/Pickup.h"
#include "Headers/Projectile.h"
#include "Headers/Tile.h"

#include <qmath.h>

extern Game *game;

PlayerCharacter::PlayerCharacter()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));

    gunArm           = new GunArm();
    aimDirection     = AimDirection::aimingRight;
    shoulderPosition = pos() + QPointF(35, 60);
    gunArm->setPos(shoulderPosition);

    m_projectileSound = new QMediaPlayer();
    m_projectileSound->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/projectile.mp3"));
}

//----------------Getters/Setters-------------------

GunArm *PlayerCharacter::getGunArm() const { return gunArm; }

int PlayerCharacter::getHealth() const { return m_health; }

bool PlayerCharacter::getSoundEffectOn() const { return m_soundEffectOn; }

void PlayerCharacter::setSoundEffectOn(bool value) { m_soundEffectOn = value; }

//------------------------------------------------

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_E && DialogueHandler::isDialogueActive && !m_isPaused)
    {
        DialogueHandler::advanceDialogue();
    }

    if(event->key() == Qt::Key_P && !m_isPaused && !game->isGameWon)
    {
        game->mainTimer->stop();
        game->music->pause();
        m_isPaused = true;
        game->getPauseLabel()->show();
    }
    else if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && m_isPaused)
    {
        game->mainTimer->start(20);
        game->playMusic();
        m_isPaused = false;
        game->getPauseLabel()->hide();
    }
    else if((event->key() == Qt::Key_O) && m_isPaused && !game->isGameWon)
    {
        Menu::options->show();
    }
    else if((event->key() == Qt::Key_H) && m_isPaused && !game->isGameWon)
    {
        Menu::help->show();
    }
    else if(event->key() == Qt::Key_R && game->getIsGameOver() == true)
    {
        game->getGameOverLabel()->hide();
        game->setIsGameOver(false);
        m_health = 8;
        emit healthChanged();
        game->levelID--;
        game->changeLevel();
    }

    if(event->key() == Qt::Key_D && !DialogueHandler::isDialogueActive && !m_isPaused)
    {
        if (game->getLevelID() == 2)
        {
            setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_right.png"));
        }
        m_canMove   = true;
        m_velocityX = 9;
    }
    else if(event->key() == Qt::Key_A  && !DialogueHandler::isDialogueActive && !m_isPaused)
    {
        if (game->getLevelID() == 2)
        {
           setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_no_gun_left.png"));
        }
        m_canMove   = true;
        m_velocityX = -9;
    }
    else if(event->key() == Qt::Key_Space && m_isOnGround  && !DialogueHandler::isDialogueActive)
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
    if(!m_isPaused && !game->getIsGameOver())
    {
        targetPoint = game->mapToScene(point);

        QLineF ln(shoulderPosition, targetPoint );
        qreal angle = -1 * ln.angle();

        if(angle > -90 || angle < -270)
        {
            aimDirection = AimDirection::aimingRight;
            gunArm->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_right.png"));
            gunArm->setTransformOriginPoint(6, 0);
            if(game->getLevelID() != 2)
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
            if(game->getLevelID() != 2)
            {
                setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_left.png"));
            }
            gunArm->setRotation(180 + angle);
        }
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
    if(!m_isPaused && !game->getIsGameOver())
    {
        auto *projectile = new Projectile(Projectile::Player);

        QLineF ln(shoulderPosition, targetPoint);
        qreal angle = -1 * ln.angle();
        qreal dy    = 80 * qSin(qDegreesToRadians(angle));
        qreal dx    = 80 * qCos(qDegreesToRadians(angle));

        projectileStartPoint = QPointF(shoulderPosition + QPointF(dx, dy));
        projectile->setPos(projectileStartPoint.x(), projectileStartPoint.y());
        projectile->setRotation(angle);

        game->currentLevel->addItem(projectile);

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
        if(y() < 0) // player is hitting the top of the scene
        {
            setPos(x(), 0);
            m_velocityY = 5;
        }

        setPos(x(), y() + m_velocityY);

        if(m_velocityY < 10)
            m_velocityY += m_gravity;
    }

    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

    game->centerOn(this);
}

void PlayerCharacter::walk()
{
    // if the player tries to move outside the playable area in the scene
    if(x() > game->currentLevel->width() - 3 * 45) // right
    {
        setPos(game->currentLevel->width() - 3 * 45, y());
    }
    else if(x() < 0) // left
    {
        setPos(0, y());
    }

    setPos(x() + m_velocityX, y());

    updateShoudlerPosition();
    gunArm->setPos(shoulderPosition);

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
                emit startDialogue();
            }
            if(typeid(*(colliding_item)) == typeid(Pickup))
            {
                increaseHealth();
                scene()->removeItem(colliding_item);
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
                }
                else if(m_playerRectPoints[3].x() < tileRectPoints[3].x() - 25 &&
                        m_playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                    setPos(x() - 11, y());
                }
                else if(m_playerRectPoints[2].x() >= tileRectPoints[2].x() &&
                        m_playerRectPoints[1].y() <= tileRectPoints[3].y() - 20)
                {
                    setPos(x() + 11, y());
                }
                if(m_playerRectPoints[1].y() <= tileRectPoints[3].y() + 10 &&
                   m_playerRectPoints[2].x() > tileRectPoints[3].x() + 2 &&
                   m_playerRectPoints[3].x() < tileRectPoints[2].x() - 2)
                {
                    m_velocityY = 5;
                }

                auto t = dynamic_cast<Tile*>(colliding_item);
                if(t->getType() == '^' || t->getType() == 'W')
                {
                    emit playerIsDead();
                }
            }
            else if(typeid(*(colliding_item)) == typeid(Portal) &&
                   (game->currentLevelPortal->x() - x()) < 30 &&
                   (game->currentLevelPortal->y() - y()) < 30)
            {
                game->currentLevel->removeItem(game->player);
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
