#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

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
        void advance (int step) override;

        void move();
        void shoot();
        void decreaseHealth();

    private:
        int m_side;
        int steps;
        bool stopMoving;
        int lives = 3;
};

#endif // ENEMYCHARACTER_H
