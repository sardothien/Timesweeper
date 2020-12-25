#ifndef LEVEL_H
#define LEVEL_H

class QGraphicsScene;

class Level
{
    public:
        // Funkcije za ucitavanje nivoa i iscrtavanja objekata
        static QGraphicsScene* LoadLevel();
        static void AddObject(QGraphicsScene *scene, char type, int x, int y);
};

#endif // LEVEL_H

