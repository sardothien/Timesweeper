#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

Pickup::Pickup(QGraphicsPixmapItem *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
    setPos(360,270);

}

