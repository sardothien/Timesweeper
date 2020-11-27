#include "Headers/Character.h"

Character::Character(QGraphicsPixmapItem *parent):QObject()
{

}

int Character::getHealth()
{
    return health;
}

void Character::increaseHealth()
{
    health += 10;
}
