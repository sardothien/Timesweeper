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
            bank,
            cantina,
            drugStore,
            generalStore,
            office,
            hotel,
            post
        };

        Building (Buildings b);
};

#endif // BUILDING_H
