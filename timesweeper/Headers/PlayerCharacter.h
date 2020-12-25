#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Headers/Character.h"
#include "Headers/GunArm.h"

class QMediaPlayer;

class PlayerCharacter : public Character
{
    Q_OBJECT
    public:
        //metode
        PlayerCharacter ();
        ~PlayerCharacter();
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        void advance(int step) override;
        void aimAtPoint(QPoint point);
        void updateShoudlerPosition();
        void shootProjectile();
        void increaseHealth();
        void decreaseHealth();


        //geteri/seteri
        GunArm *getGunArm() const;
        int getHealth() const;

        enum AimDirection
        {
            aimingLeft,
            aimingRight
        };

        //polja
        AimDirection aimDirection;
        QPointF targetPoint;
        GunArm *gunArm;
        QPointF projectileStartPoint;
        QPointF shoulderPosition;

    signals:
        void enteredPortal();
        void startDialogue();
        void healthChanged();
        void playerIsDead();

    private slots:
        void jump();
        void walk();
        void detectCollision();

    private:
        int health = 8;
        qreal velocityX;
        qreal velocityY = 1;
        qreal gravity = 0.5;
        bool isOnGround;
        bool isPaused = false;
        bool canMove = false;
        QMediaPlayer *projectilesound;
        QGraphicsPixmapItem *pauseScreen;
        QPolygonF playerRectPoints;
};

#endif // PLAYERCHARACTER_H
