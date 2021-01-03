#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "Headers/Character.h"
#include "Headers/EnemyHealthBar.h"

class EnemyBoss : public Character
{
    Q_OBJECT
    public:
        EnemyBoss();

        void setLives(int lives);
        int getLives() const;

        void decreaseHealth();

    signals:
        void alphaDied();
        void alphaEscaped();

    private:
        void advance(int phase) override;
        void move();
        void drawHealthBar();

    private:
        int m_lives = 80;
};

#endif // ENEMYBOSS_H
