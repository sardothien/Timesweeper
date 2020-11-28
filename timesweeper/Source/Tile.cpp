#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(QGraphicsPixmapItem *parent)
{
    if(game->levelID == 1){ // TODO - promeniti tile za ovaj nivo!
        setPixmap(QPixmap(":/Images/Resources/testtile.png"));
    }
    else if(game->levelID == 2)
        setPixmap(QPixmap(":/Images/Resources/single_tile_lvl2.png"));
    // else if(game->levelID == 3)
        // ...

}
