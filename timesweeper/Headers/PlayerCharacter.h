#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Headers/Character.h"
#include "Headers/GunArm.h"

class QMediaPlayer;

class PlayerCharacter : public Character
{
    Q_OBJECT
    public:
        // Methods
        PlayerCharacter();

        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;

        void aimAtPoint(QPoint point);
        void updateShoudlerPosition();
        void shootProjectile();
        void increaseHealth();
        void decreaseHealth();

        // Getters/Setters
        GunArm *getGunArm() const;
        int getHealth() const;
        bool getSoundEffectOn() const;
        void setSoundEffectOn(bool value);

        enum AimDirection
        {
            aimingLeft,
            aimingRight
        };

        // Fields
        AimDirection aimDirection;
        QPointF targetPoint;
        GunArm *gunArm;
        QPointF projectileStartPoint;
        QPointF shoulderPosition;

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
        bool m_soundEffectOn = true;
        QMediaPlayer *m_projectileSound;
        QPolygonF m_playerRectPoints;
};

#endif // PLAYERCHARACTER_H
