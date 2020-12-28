#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Tile(char tile);
        ~Tile();

        char getType() const;

    private:
        void drawTile();
        void advance(int phase) override;
        void move();

    private:
        int m_side;
        int m_steps;
        bool m_stopMoving;
        char m_type;
};

#endif // TILE_H
