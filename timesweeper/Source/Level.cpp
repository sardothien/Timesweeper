#include <iostream>
#include <fstream>
#include <string>
#include <QDir>
#include <QFile>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QString>

#include "Headers/Level.h"
#include "Headers/Game.h"


QGraphicsScene* Level::LoadLevel(std::string path, int sizeX, int sizeY)
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 12000,700);

    char tile;

    std::fstream levelFile;
    levelFile.open(path);
    if(levelFile.fail()){
        std::cout << "File not found/loaded!" << std::endl;
        return nullptr;
    }

    for(int y = 0; y < sizeY; y++){
        for(int x = 0; x < sizeX; x++){
            levelFile.get(tile);
            // std::cout << tile << " " << x << " " << y << std::endl;
            AddObject(scene, tile, x*32, y*32);
        }
    }

    levelFile.close();

    return scene;
}

void Level::AddObject(QGraphicsScene *scene, char type, int x, int y)
{
    QGraphicsRectItem *rect;
    switch(type){
        case '#':
            rect = new QGraphicsRectItem();
            rect->setRect(x, y, 16, 16);
            scene->addItem(rect);
            break;
        case '=':
            rect = new QGraphicsRectItem();
            rect->setRect(x, y, 16, 16);
            scene->addItem(rect);
            break;
        case 'E':
            rect = new QGraphicsRectItem();
            rect->setRect(x, y, 32, 32);
            scene->addItem(rect);
            break;
        default:
            break;
    }
}
