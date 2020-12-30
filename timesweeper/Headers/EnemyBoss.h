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

        void setLives(int lives);
        int getLives() const;

        void decreaseHealth();

    private:
        void advance(int phase) override;
        void move();
        void drawHealthBar();

    private:
        int m_lives    = 80;
        int m_maxLives = 80;
};

#endif // ENEMYBOSS_H
