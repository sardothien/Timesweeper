#ifndef LEVEL_H
#define LEVEL_H

#include <Headers/Building.h>

class QGraphicsScene;
class QString;

class Level
{
    public:
        static QGraphicsScene* LoadLevel();
        static QGraphicsScene *m_scene;

    private:
        static void parseLevelFile(QString filename);
        static void AddObject(char type, int x, int y);
        static void addBuilding(Building::Buildings b, int x, int y);
};

#endif // LEVEL_H
