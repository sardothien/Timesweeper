#ifndef TILE_H
#define TILE_H

#include <QTimer>
#include <QGraphicsPixmapItem>

class Tile :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Tile (char tile, QGraphicsPixmapItem *parent = nullptr);

        char getType() const;

public slots:
        void move();

    private:
        int side;
        int steps;
        bool stopMoving;
        char type;
        QTimer *timerWalk;
};

#endif // TILE_H
