#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "Headers/Character.h"
#include "Headers/HealthBar.h"

class EnemyBoss : public Character
{
    Q_OBJECT
    public:
        EnemyBoss(Character *parent = 0);
        ~EnemyBoss();

        HealthBar* m_healthBar;
        HealthBar *getHealtBar() const;

        void setLives(int lives);
        int getLives() const;

    private:
        void advance(int step) override;
        void decreaseHealth();
        void move();

    private:
        int m_lives    = 20;
        int m_maxLives = 20;
};

#endif // ENEMYBOSS_H
