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
#include "Headers/Pickup.h"

extern Game* game;
EnemyCharacter* Level::enemy;

QGraphicsScene* Level::LoadLevel()
{

    // Pravljenje scene
    QGraphicsScene *scene = new QGraphicsScene();

    QString filename;

    // Biranje nivoa
    if(game->levelID == 1){
        filename = ":/Levels/Resources/level1.txt";
    }
    else if(game->levelID == 2){
        filename = ":/Levels/Resources/level2.txt";
    }
    else if(game->levelID == 3){
        filename = ":/Levels/Resources/level3.txt";
    }
    else if(game->levelID == 4){
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

    // 45x45 - dimenzija tile-a
    scene->setSceneRect(0, 0, 45*(sizeX-1), 700);

    // Prolazak kroz matricu i iscrtavanje
    for(int y = 0; y < sizeY; y++){
        QString tiles = in.readLine();
        for(int x = 0; x < sizeX-1; x++){
            if(game->levelID == 1) // TODO - obrisati kasnije
                AddObject(scene, tiles[x].toLatin1(), x*44, y*44);
            else // ostali nivoi (45x45 - dimenzija tile-a)
                AddObject(scene, tiles[x].toLatin1(), x*45, y*45);
        }
    }

    file.close();

    return scene;
}

void Level::AddObject(QGraphicsScene *scene, char type, int x, int y)
{
    Tile *rect;
    Pickup *pickup;

    switch(type){
        case '-': // nista
            break;
        case 'E': // neprijatelj
            enemy = new EnemyCharacter();
            enemy->setPos(x, y);
            enemy->setScale(2);
            enemy->healthBar->bar->setPos(x, y-35);
            scene->addItem(enemy);
            scene->addItem(enemy->healthBar->bar);
            break;
        case '+': // zivoti
            pickup = new Pickup();
            pickup->setPos(x, y);
            scene->addItem(pickup);
            break;
        default: // sve ostale prepreke
            rect = new Tile(type);
            rect->setPos(x, y);
            scene->addItem(rect);
            break;
    }
}
