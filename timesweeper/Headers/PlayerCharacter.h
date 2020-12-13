#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

#include "Headers/Character.h"
#include "Headers/GunArm.h"

class PlayerCharacter : public Character
{
    Q_OBJECT
    public:
        PlayerCharacter (Character *parent = nullptr);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void shootProjectile();
        void aimAtPoint(QPoint point);
        QPoint targetPoint;
        GunArm *gunArm;
        enum AimDirection
        {
            aimingLeft,
            aimingRight
        };
        AimDirection aimDirection;

        GunArm *getGunArm() const;
        int getHealth();
        void increaseHealth();

signals:
        void enteredPortal();
        void nearNPC();
        void healthPickedUp();

    public slots:

    private slots:
        void jump();
        void walk();
        void detectCollision();

    private:
        QTimer *timerJump,*timerWalk,*timerCollision;
        qreal velocityX, velocityY = 1;
        qreal gravity = 0.5;
        bool isOnGround;
        QMediaPlayer *projectilesound;
        QPolygonF playerRectPoints;
        int health = 5;
};

#endif // PLAYERCHARACTER_H
