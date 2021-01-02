#include "Headers/Tile.h"
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"

extern Game *game;

Tile::Tile(char tile)
    : m_type(tile)
{
    // helper variables for platform movement
    m_side       = 0;
    m_steps      = 0;
    m_stopMoving = false;

    drawTile();
}

char Tile::getType() const { return m_type; }

void Tile::drawTile()
{
    if(game->getLevelID() == 1)
    {
        setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_1_Tiles/floor_tile.png"));
    }
    else if(game->getLevelID() == 2)
    {
        if(m_type == '=')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_lvl2.png"));
        }
        else if(m_type == '#')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/inner_tile_lvl2.png"));
        }
        else if(m_type == '^')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/spikes_lvl2.png"));
        }
        else if(m_type == '|')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/step_tile_lvl2.png"));
        }
        else if(m_type == '?')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_spec_lvl2.png"));
        }
        else if(m_type == 'x')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/single_tile_rot_lvl2.png"));
        }
        else if(m_type == '*')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_2_Tiles/step_tile_rot_lvl2.png"));
        }
    }
    else if(game->getLevelID() == 3)
    {
        if(m_type == '=')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/single_tile_lvl3.png"));
        }
        else if(m_type == '#')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/underground_tile_lvl3.png"));
        }
        else if(m_type == 'W')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/water_tile_lvl3.png"));
        }
        else if(m_type == 'L')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/leftside_tile_lvl3.png"));
        }
        else if(m_type == 'R')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/rightside_tile_lvl3.png"));
        }
        else if(m_type == 'l')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/rightside_down_lvl3.png"));
        }
        else if(m_type == 'r')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/leftside_down_lvl3.png"));
        }
        else if(m_type == '1')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/left_platform.png"));
        }
        else if(m_type == '2')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/right_platform.png"));
        }
        else if(m_type == '3')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/ugao1.png"));
        }
        else if(m_type == '4')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/ugao2.png"));
        }
        else if(m_type == 'M')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/single_tile_lvl3.png"));
        }
        else if(m_type == '^')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/bodlje.png"));
        }
        else if(m_type == 'D')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_3_Tiles/down.png"));
        }
    }
    else if(game->getLevelID() == 4)
    {
        if(m_type == '=')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/single_tile_lvl4.png"));
        }
        else if(m_type == '#')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/inner_tile_lvl4.png"));
        }
        else if(m_type == '*')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_tile_lvl4.png"));
        }
        else if(m_type == 'l')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_left_tile_lvl4.png"));
        }
        else if(m_type == 'r')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/platform_right_tile_lvl4.png"));
        }
        else if(m_type == '1')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_1_lvl4.png"));
        }
        else if(m_type == '2')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_2_lvl4.png"));
        }
        else if(m_type == '3')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_3_lvl4.png"));
        }
        else if(m_type == '4')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_4_lvl4.png"));
        }
        else if(m_type == '5')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_5_lvl4.png"));
        }
        else if(m_type == '6')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_6_lvl4.png"));
        }
        else if(m_type == '7')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_7_lvl4.png"));
        }
        else if(m_type == '8')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_8_lvl4.png"));
        }
        else if(m_type == '9')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_9_lvl4.png"));
        }
        else if(m_type == '~')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/tile_down_lvl4.png"));
        }
        else if(m_type == 't')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/crate_lvl4.png"));
        }
        else if(m_type == 'n')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/stone_lvl4.png"));
        }
        else if(m_type == '^')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_4_Tiles/spikes_lvl4.png"));
        }
        else if(m_type == 'i')
        {
            setPixmap(QPixmap(":/Other/Resources/Other/sign_level_4.png"));
        }
    }
    else if(game->getLevelID() == 5)
    {
        if(m_type == '=')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/middle_tile_lvl5.png"));
        }
        else if(m_type == '#')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/inner_tile_lvl5.png"));
        }
        else if(m_type == '%')
        {
            setPixmap(QPixmap(":/Terrain/Resources/Terrain/Level_5_Tiles/paltform_tile_lvl5.png"));
        }
    }
}

void Tile::advance(int phase)
{
    QGraphicsItem::advance(phase);
    if(m_type == 'M')
    {
        move();
    }
}

void Tile::move()
{
    if(m_side == 0) // mobing right
    {
        if(!m_stopMoving)
        {
            if(game->m_player->collidesWithItem(this))
            {
                game->m_player->setPos(game->m_player->x() + 2,
                                     game->m_player->y());
            }

            setPos(x() + 2, y());

            m_steps++;
            if(m_steps == 120)
            {
                m_side  = 1;
                m_steps = 0;
            }
        }
    }
    else if(m_side == 1) // moiving left
    {
        if(!m_stopMoving)
        {
            if(game->m_player->collidesWithItem(this))
            {
                game->m_player->setPos(game->m_player->x() - 2,
                                     game->m_player->y());
            }

            setPos(x() - 2, y());

            m_steps++;
            if(m_steps == 120)
            {
                m_side  = 0;
                m_steps = 0;
            }
        }
    }
}
