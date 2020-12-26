#include "Headers/Pickup.h"
#include "Headers/Game.h"

extern Game *game;

Pickup::Pickup()
{
    if(game->getLevelID() == 2)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_2.png"));
    }
    else if(game->getLevelID() == 3)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_3.png"));
    }
    else if(game->getLevelID() == 4)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/health_level_4.png"));
    }
    else
    {
        setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
    }
}
