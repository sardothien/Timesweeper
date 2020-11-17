#ifndef ENEMYCHARACTER_H
#define ENEMYCHARACTER_H

#include "Headers/Character.h"

class EnemyCharacter : public Character
{
    public:
        EnemyCharacter (Character *parent = nullptr);
};

#endif // ENEMYCHARACTER_H
