#include "Headers/Game.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

Pickup::Pickup(QGraphicsPixmapItem *parent)
{
    if(game->levelID == 2)
        setPixmap(QPixmap(":/Images/Resources/Level2Tiles/health_tile_lvl2.png"));
    else
        setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
}

