#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

#include "Headers/Character.h"

class PlayerCharacter : public Character
{
    Q_OBJECT
    public:
        PlayerCharacter (Character *parent = nullptr);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void shootProjectile();

    signals:
        void enteredPortal();
        void nearNPC();

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
};

#endif // PLAYERCHARACTER_H
