#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Headers/Character.h"
#include "Headers/GunArm.h"

class QMediaPlayer;

class PlayerCharacter : public Character
{
    Q_OBJECT
    public:
        // metode
        PlayerCharacter();
        ~PlayerCharacter();

        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;

        void aimAtPoint(QPoint point);
        void updateShoudlerPosition();
        void shootProjectile();
        void increaseHealth();
        void decreaseHealth();

        // geteri/seteri
        GunArm *getGunArm() const;
        int getHealth() const;

        enum AimDirection
        {
            aimingLeft,
            aimingRight
        };

        // polja
        AimDirection m_aimDirection;
        QPointF m_targetPoint;
        GunArm *m_gunArm;
        QPointF m_projectileStartPoint;
        QPointF m_shoulderPosition;

    private:
        void advance(int phase) override;
        void jump();
        void walk();
        void detectCollision();

    signals:
        void enteredPortal();
        void startDialogue();
        void healthChanged();
        void playerIsDead();

    private:
        qreal m_velocityX;
        qreal m_velocityY = 1;
        qreal m_gravity   = 0.5;
        int m_health      = 8;
        bool m_isPaused   = false;
        bool m_canMove    = false;
        bool m_isOnGround;
        QMediaPlayer *m_projectileSound;
        QPolygonF m_playerRectPoints;
};

#endif // PLAYERCHARACTER_H
