#include "Headers/Game.h"
#include "Headers/Pickup.h"

extern Game *game;

Pickup::Pickup()
{
    if(game->levelID == 2)
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_2.png"));
    else if(game->levelID == 4)
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_4.png"));
    else
        setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
}

