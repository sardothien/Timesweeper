#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

class Tile : public QGraphicsPixmapItem
{
    public:
        Tile (char tile, QGraphicsPixmapItem *parent = nullptr);
};

#endif // TILE_H
