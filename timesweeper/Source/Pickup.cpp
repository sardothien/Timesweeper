#include "Headers/Pickup.h"
#include "Headers/Game.h"

extern Game *game;

Pickup::Pickup()
{
    setPixmap(QPixmap(":/Other/Resources/Other/health_level_" + QString::number(game->getLevelID()) + ".png"));
}
