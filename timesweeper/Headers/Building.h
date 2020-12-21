#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsPixmapItem>

class Building : public QGraphicsPixmapItem
{
    public:
        enum Buildings
        {
            sheriff,
            saloon,
            bigSaloon,
            bank,
            office,
            generalStore,
            hotel,
            church
        };

        Building (Buildings b);
};

#endif // BUILDING_H
