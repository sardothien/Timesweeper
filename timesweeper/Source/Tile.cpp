#include "Headers/Game.h"
#include "Headers/Tile.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

Tile::Tile(QGraphicsPixmapItem *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testtile.png"));

}
