#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include <QTimer>

#include "Headers/Character.h"

class EnemyCharacter : public Character
{
    public:
        EnemyCharacter (Character *parent = 0);

    public slots:
        void move();

    private:
        QTimer* timerWalk;
        int index;
        int num;
};

#endif // ENEMYCHARACTER_H
