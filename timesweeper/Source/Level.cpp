#include <iostream>
#include <fstream>
#include <string>
#include <QCharRef>
#include <QFile>
#include <QGraphicsScene>
#include <QString>
#include <QTextStream>

#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Tile.h"

QGraphicsScene* Level::LoadLevel(int levelID)
{

    // Pravljenje scene
    QGraphicsScene *scene = new QGraphicsScene();

    QString filename;

    // Biranje nivoa
    if(levelID == 1){
        filename = ":/Levels/Resources/level1.txt";
    }
    else if(levelID == 2){
        filename = ":/Levels/Resources/level2.txt";
    }
    else if(levelID == 3){
        filename = ":/Levels/Resources/level3.txt";
    }
    else if(levelID == 4){
        filename = ":/Levels/Resources/level4.txt";
    }
    else{
        std::cout << "Nije dobar ID nivoa!" << std::endl;
        return nullptr;
    }

    // Otvaranje datoteke sa nivoom
    QFile file(filename);
    if(!file.exists()){
        std::cout << "Fajl ne postoji!" << std::endl;
        return nullptr;
    }
    if(!file.open(QIODevice::ReadOnly)){
        std::cout << "Nije uspelo otvaranje fajla!" << std::endl;
        return nullptr;
    }

    // Citanje podataka
    QTextStream in(&file);

    // U prvoj liniji su dimenzije matrice
    QStringList line = in.readLine().split(" ");
    int sizeX = line[0].toInt();
    int sizeY = line[1].toInt();
    //std::cout << sizeX << std::endl;
    //std::cout << sizeY << std::endl;

    scene->setSceneRect(0, sizeY*32-700, 32*(sizeX-1),700);

    // Prolazak kroz matricu i iscrtavanje
    for(int y = 0; y <= sizeY; y++){
        QString tiles = in.readLine();
        for(int x = 0; x <= sizeX; x++){
            // std::cout << tiles[x].toLatin1() << " " << x << " " << y << std::endl;
            AddObject(scene, tiles[x].toLatin1(), x*30, y*30);
        }
    }

    file.close();

    return scene;
}

void Level::AddObject(QGraphicsScene *scene, char type, int x, int y)
{
    Tile *rect;
    switch(type){
        case '#':
            rect = new Tile();
            rect->setPos(x, y);
            rect->setScale(2);
            scene->addItem(rect);
            break;
        case '=':
            rect = new Tile();
            rect->setPos(x, y);
            rect->setScale(2);
            scene->addItem(rect);
            break;
        case 'E':
            rect = new Tile();
            rect->setPos(x, y);
            rect->setScale(2);
            scene->addItem(rect);
            break;
        default:
            break;
    }
}
