#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include <QTimer>

#include "Headers/Character.h"
#include "Headers/HealthBar.h"

class EnemyCharacter : public Character
{
    Q_OBJECT
    public:
        EnemyCharacter (Character *parent = 0);
        ~EnemyCharacter();

        int getLives() const;
        void setLives(int lives);

        HealthBar* healthBar;

    public slots:
        void move();
        void decreaseHealth();
        void shoot();

    private:
        QTimer *timerWalk;
        QTimer *timerHealth;
        QTimer *timerShoot;
        int side;
        int steps;
        bool stopMoving;
        int lives = 3;
};

#endif // ENEMYCHARACTER_H
