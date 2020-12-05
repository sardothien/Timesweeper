#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

Pickup::Pickup(QGraphicsPixmapItem *parent)
{
    if(game->levelID == 2)
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_2.png"));
    else
        setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
}

