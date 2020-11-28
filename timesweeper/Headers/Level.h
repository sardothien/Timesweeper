#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include "EnemyCharacter.h"

class Level
{
    public:
        // Funkcije za ucitavanje nivoa i iscrtavanja objekata
        static QGraphicsScene* LoadLevel();
        static void AddObject(QGraphicsScene *scene, char type, int x, int y);
};

#endif // LEVEL_H

