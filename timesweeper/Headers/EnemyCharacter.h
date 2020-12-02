#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include <QTimer>

#include "Headers/Character.h"
#include "Headers/HealthBar.h"

class EnemyCharacter : public Character
{
    public:
        EnemyCharacter (Character *parent = 0);
        ~EnemyCharacter();

        int getLives() const;
        void setLives(int lives);

        HealthBar* healthBar;

    public slots:
        void move();

    private:
        QTimer* timerWalk;
        int index;
        int num;
        int lives = 3;
};

#endif // ENEMYCHARACTER_H
