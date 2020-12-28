#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "Headers/Character.h"
#include "Headers/EnemyHealthBar.h"

class EnemyBoss : public Character
{
    Q_OBJECT
    public:
        EnemyBoss();
        ~EnemyBoss();

        EnemyHealthBar* m_healthBar;
        EnemyHealthBar *getHealtBar() const;

        void setLives(int lives);
        int getLives() const;

    private:
        void advance(int phase) override;
        void decreaseHealth();
        void move();

    private:
        int m_lives    = 20;
        int m_maxLives = 20;
};

#endif // ENEMYBOSS_H
