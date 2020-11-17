#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>

class Character : public QGraphicsPixmapItem
{
    public:
        Character (QGraphicsPixmapItem *parent = nullptr);
};

#endif // CHARACTER_H
