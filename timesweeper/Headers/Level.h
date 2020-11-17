#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Level : public QGraphicsView
{
    public:
        Level (QWidget *parent = nullptr);

        QGraphicsScene *scene;

        // Funkcije za ucitavanje nivoa i iscrtavanja objekata
        void LoadLevel(std::string path, int sizeX, int sizeY);
        void AddObject(char type, int x, int y);
};

#endif // LEVEL_H

