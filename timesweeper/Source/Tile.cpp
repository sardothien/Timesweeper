#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(char tile, QGraphicsPixmapItem *parent)
{
    if(game->levelID == 1){ // TODO - promeniti tile za ovaj nivo!
        setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_1_Tiles/floor_tile.png"));
    }
    else if(game->levelID == 2){
        if(tile == '=') // pod
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_lvl2.png"));
        else if(tile == '#') // unutrasnjost
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/inner_tile_lvl2.png"));
        else if(tile == '|') // stepenice
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/step_tile_lvl2.png"));
    }
    // else if(game->levelID == 3)
        // ...

}
