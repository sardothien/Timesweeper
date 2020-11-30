#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(char tile, QGraphicsPixmapItem *parent)
{
    if(game->levelID == 1){ // TODO - promeniti tile za ovaj nivo!
        setPixmap(QPixmap(":/Images/Resources/testtile.png"));
    }
    else if(game->levelID == 2){
        if(tile == '=') // pod
            setPixmap(QPixmap(":/Images/Resources/Level2Tiles/single_tile_lvl2.png"));
        else if(tile == '#') // unutrasnjost
            setPixmap(QPixmap(":/Images/Resources/Level2Tiles/inner_tile_lvl2.png"));
        else if(tile == '|') // stepenice
            setPixmap(QPixmap(":/Images/Resources/Level2Tiles/step_tile_lvl2.png"));
    }
    // else if(game->levelID == 3)
        // ...

}
