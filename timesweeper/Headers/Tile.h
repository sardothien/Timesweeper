#ifndef TILE_H
#define TILE_H

#include <QTimer>
#include <QGraphicsPixmapItem>

class Tile :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Tile (char tile, QGraphicsPixmapItem *parent = nullptr);
        ~Tile();

        char getType() const;

        void advance(int step) override;
        void move();

    private:
        int side;
        int steps;
        bool stopMoving;
        char type;
};

#endif // TILE_H
