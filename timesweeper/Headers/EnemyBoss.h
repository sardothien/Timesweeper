#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H


#include "Headers/Character.h"
#include "Headers/HealthBar.h"

class EnemyBoss : public Character
{
    Q_OBJECT
    public:
        EnemyBoss (Character *parent = 0);
        ~EnemyBoss();

        HealthBar* healthBar;

        void setLives(int lives);
        int getLives() const;

    //public slots:
        void advance(int step) override;
        void decreaseHealth();
        void move();

    private:
        int lives = 20;
        int maxLives = 20;
};

#endif // ENEMYBOSS_H
