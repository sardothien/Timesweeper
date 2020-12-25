#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

class Tile :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        //metode
        Tile (char tile);
        ~Tile();
        void advance(int step) override;
        void move();

        //geteri/seteri
        char getType() const;

    private:
        int side;
        int steps;
        bool stopMoving;
        char type;
};

#endif // TILE_H
