#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "Headers/Character.h"

class PlayerCharacter : public Character
{
    public:
        PlayerCharacter (Character *parent = nullptr);
        void keyPressEvent(QKeyEvent *event);
};

#endif // PLAYERCHARACTER_H
