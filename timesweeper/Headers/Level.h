#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>

class Level
{
    public:
        // Funkcije za ucitavanje nivoa i iscrtavanja objekata
        static QGraphicsScene* LoadLevel(std::string path, int sizeX, int sizeY);
        static void AddObject(QGraphicsScene *scene, char type, int x, int y);
};

#endif // LEVEL_H

