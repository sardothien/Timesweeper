#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Headers/Character.h"

#include <QList>
#include <QPointF>
#include <QTimer>

class EnemyCharacter : public Character
{
    public:
        EnemyCharacter (Character *parent = 0);
        void rotate(QPointF p);

    public slots:
        void move();

    private:
        QTimer* timerWalk;
        int index;
        int num;
};

#endif // ENEMYCHARACTER_H
