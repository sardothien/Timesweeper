#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(char tile, QGraphicsPixmapItem *parent)
{
    if(game->levelID == 1){
        setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_1_Tiles/floor_tile.png"));
    }
    else if(game->levelID == 2){
        if(tile == '=')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_lvl2.png"));
        else if(tile == '#')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/inner_tile_lvl2.png"));
        else if(tile == '|')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/step_tile_lvl2.png"));
        else if(tile == '?')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_spec_lvl2.png"));
        else if(tile == 'x')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_rot_lvl2.png"));
        else if(tile == '*')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/step_tile_rot_lvl2.png"));
    }
    else if(game->levelID == 3)
    {

    }
    else if(game->levelID == 4)
    {
        if(tile == '=') // pod
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/single_tile_lvl4.png"));
        else if(tile == '#') // unutrasnjost
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/inner_tile_lvl4.png"));
        else if(tile == '*') // platforma
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_tile_lvl4.png"));
        else if(tile == 'l') // leva ivica platforme
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_left_tile_lvl4.png"));
        else if(tile == 'r') // desna ivica platforme
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_right_tile_lvl4.png"));
        else if(tile == '1')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_1_lvl4.png"));
        else if(tile == '2')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_2_lvl4.png"));
        else if(tile == '3')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_3_lvl4.png"));
        else if(tile == '4')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_4_lvl4.png"));
        else if(tile == '5')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_5_lvl4.png"));
        else if(tile == '6')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_6_lvl4.png"));
        else if(tile == '7')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_7_lvl4.png"));
        else if(tile == '8')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_8_lvl4.png"));
        else if(tile == '9')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_9_lvl4.png"));
        else if(tile == '~')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_down_lvl4.png"));

    }
    else if(game->levelID == 5){
        if(tile == '=') // pod
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/middle_tile_lvl5.png"));
        else if(tile == '#') // unutrasnjost
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/inner_tile_lvl5.png"));
        else if(tile == '%') // platforma
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/paltform_tile_lvl5.png"));
    }

}
