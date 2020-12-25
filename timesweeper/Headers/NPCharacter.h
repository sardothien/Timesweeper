#ifndef NPCHARACTER_H
#define NPCHARACTER_H

#include "Headers/Character.h"

class NPCharacter : public QObject, public QGraphicsPixmapItem
{
    public:
        NPCharacter (QGraphicsPixmapItem *parent = nullptr);
        ~NPCharacter();
};

#endif // NPCHARACTER_H
