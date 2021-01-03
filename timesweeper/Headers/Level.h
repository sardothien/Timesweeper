#ifndef LEVEL_H
#define LEVEL_H

#include <Headers/Building.h>

class QGraphicsScene;
class QString;

class Level
{
    public:
        static QGraphicsScene* loadLevel();

    private:
        static void parseLevelFile(QString filename);
        static void addObject(char type, int x, int y);
        static void addBuilding(Building::Buildings b, int x, int y);

    private:
        static QGraphicsScene *m_scene;
};

#endif // LEVEL_H
