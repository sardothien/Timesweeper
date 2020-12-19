#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(char tile, QGraphicsPixmapItem *parent):QObject()
{

    // pomocne promenljive za kretanje
    side = 0;
    steps = 0;
    stopMoving = false;

    // timer za move()
    if(tile == 'M')
    {
        timerWalk = new QTimer();
        connect(timerWalk, &QTimer::timeout, this, &Tile::move);
        timerWalk->start(15);
    }

    type = tile;

    if(game->levelID == 1){
        setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_1_Tiles/floor_tile.png"));
    }
    else if(game->levelID == 3){
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
    else if(game->levelID == 2)
    {
        if(tile == '=')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/single_tile_lvl3.png"));
        else if(tile == '#')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/underground_tile_lvl3.png"));
        else if(tile == 'W')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/water_tile_lvl3.png"));
        else if(tile == 'L')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/leftside_tile_lvl3.png"));
        else if(tile == 'R')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/rightside_tile_lvl3.png"));
        else if(tile == 'l')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/rightside_down_lvl3.png"));
        else if(tile == 'r')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/leftside_down_lvl3.png"));
        else if(tile == '1')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/left_platform.png"));
        else if(tile == '2')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/right_platform.png"));
        else if(tile == 'M')
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/single_tile_lvl3.png"));
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

void Tile::move()
{
    if(type == 'M')
    {
        if(side == 0) // okrenut ka desno
        {
            if(!stopMoving)
            {
                if(game->player->collidesWithItem(this))
                    game->player->setPos(game->player->x()+1,game->player->y());

                setPos(x()+1, y());

                steps++;
                if(steps == 430){
                    side = 1;
                    steps = 0;
                }
            }
        }
        else if(side == 1) // okrenut ka levo
        {
            if(!stopMoving)
            {
                if(game->player->collidesWithItem(this))
                    game->player->setPos(game->player->x()-1, game->player->y());

                setPos(x()-1, y());

                steps++;
                if(steps == 430){
                    side = 0;
                    steps = 0;
                }
            }
        }
    }
}

char Tile::getType() const
{
    return type;
}
