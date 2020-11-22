#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QTimer>
#include "Headers/Character.h"

class PlayerCharacter : public Character
{
    public:
        PlayerCharacter (Character *parent = nullptr);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        int getHealth();
        void increaseHealth();
    signals:

    public slots:

    private slots:
        void jump();
        void walk();
        void detectCollision();
    private:
        QTimer *timerJump,*timerWalk,*timerCollision;
        qreal velocityX = 15, velocityY = 1;
        qreal gravity = 0.5;
        bool isOnGround;
        int health = 50;

};

#endif // PLAYERCHARACTER_H
