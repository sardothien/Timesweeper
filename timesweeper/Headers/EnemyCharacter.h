#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Headers/Character.h"
#include "Headers/EnemyHealthBar.h"

class EnemyCharacter : public Character
{
    Q_OBJECT
    public:
        EnemyCharacter();
        ~EnemyCharacter();

        int getLives() const;
        void setLives(int lives);

        EnemyHealthBar* m_healthBar;
        EnemyHealthBar *getHealtBar() const;

        void decreaseHealth();

    private:
        void advance (int phase) override;
        void move();
        void shoot();        

    private:
        int m_side;
        int m_steps;
        bool m_stopMoving;
        int m_timeToShoot = 0;
        int m_lives       = 3;
};

#endif // ENEMYCHARACTER_H
