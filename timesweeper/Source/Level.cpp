#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <QCharRef>
#include <QFile>
#include <QGraphicsScene>
#include <QString>
#include <QTextStream>

#include "Headers/Game.h"
#include "Headers/NPCharacter.h"
#include "Headers/Level.h"
#include "Headers/Tile.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Portal.h"
#include "Headers/Building.h"

extern Game* game;
EnemyCharacter* Level::enemy;
NPCharacter *Game::currentLevelNpc;
PlayerCharacter *Game::player;
Portal *Game::currentLevelPortal;
QPointF Game::currentLevelPlayerStartPosition;

QGraphicsScene* Level::LoadLevel()
{
    // Pravljenje scene
    QGraphicsScene *scene = new QGraphicsScene();

    QString filename;

    // Biranje nivoa
    if(game->levelID == 1){
        filename = ":/Levels/Resources/Levels/level1.txt";
        scene->setSceneRect(0, 0, 2300, 700);
        scene->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_1_prologue.png")));
    }
    else if(game->levelID == 2){
        filename = ":/Levels/Resources/Levels/level2.txt";
        scene->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_2_maya.png")));
    }
    else if(game->levelID == 3){
        filename = ":/Levels/Resources/Levels/level3.txt";
    }
    else if(game->levelID == 4){
        filename = ":/Levels/Resources/Levels/level4.txt";
        scene->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_4_wild_west.png")));
    }
    else if(game->levelID == 5){
        filename = ":/Levels/Resources/Levels/level5.txt";
        scene->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_5_final.png")));
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
    if(game->levelID == 1)
        scene->setSceneRect(0, 0, 44*(sizeX-1), 700);
    else if(game->levelID == 5)
        scene->setSceneRect(0, 0, 45*(sizeX-1), 45*(sizeY-1));
    else
        scene->setSceneRect(0, 0, 45*(sizeX-1), 700);

    // Prolazak kroz matricu i iscrtavanje
    for(int y = 0; y < sizeY; y++){
        QString tiles = in.readLine();
        for(int x = 0; x < sizeX-1; x++){
            if(game->levelID == 1)
                AddObject(scene, tiles[x].toLatin1(), x*44, y*44);
            else // ostali nivoi (45x45 - dimenzija tile-a)
                AddObject(scene, tiles[x].toLatin1(), x*45, y*45);
        }
    }

    file.close();

    return scene;
}

void addBuilding(Building::Buildings b, QGraphicsScene *scene, int x, int y)
{
    Building *building;

    building = new Building(b);
    building->setPos(x,y);
    scene->addItem(building);
}

void Level::AddObject(QGraphicsScene *scene, char type, int x, int y)
{
    Tile *rect;
    Pickup *pickup;
    NPCharacter *npc;
    Portal *portal;


    switch(type)
    {
        case '-': // nista
            break;
        case 'E': // neprijatelj
            enemy = new EnemyCharacter();
            enemy->setPos(x, y-110);
            enemy->setScale(0.8);
            enemy->healthBar->barFrame->setPos(x, y-135);
            enemy->healthBar->bar->setPos(x, y-135);
            scene->addItem(enemy);
            scene->addItem(enemy->healthBar->barFrame);
            scene->addItem(enemy->healthBar->bar);
            break;
        case '+': // zivoti
            pickup = new Pickup();
            pickup->setPos(x, y);
            scene->addItem(pickup);
            break;
        case 'N': //NPC
            npc = new NPCharacter();
            npc->setPos(x,y);
            scene->addItem(npc);
            game->setCurrentLevelNpc(npc);
            //qDebug() << game->getCurrentLevelNpcPosition();
            break;
        case 'P': //Portal
            portal = new Portal();
            portal->setPos(x,y);
            scene->addItem(portal);
            game->setCurrentLevelPortal(portal);
            //qDebug() << game->getCurrentLevelPortalPosition();
            break;
        case 'S': //Portal
            Game::currentLevelPlayerStartPosition = QPointF(x, y);
            //qDebug() << Game::currentLevelPlayerStartPosition;
            break;
         default: // sve ostale prepreke
            rect = new Tile(type);
            rect->setPos(x, y);
            scene->addItem(rect);
            break;
    }

    if (game->getLevelID()==4)
    {
        switch(type)
        {
        case 's': //Building - level 4 - sheriff
            addBuilding(Building::Buildings::sheriff, scene, x, y);
            break;
        case 'a': //Building - level 4 - saloon
            addBuilding(Building::Buildings::saloon, scene, x, y);
            break;
         case 'b': //Building - level 4 - bank
            addBuilding(Building::Buildings::bank, scene, x, y);
            break;
        case 'c': //Building - level 4 - cantina
            addBuilding(Building::Buildings::cantina, scene, x, y);
            break;
        case 'd': //Building - level 4 - drugStore
            addBuilding(Building::Buildings::drugStore, scene, x, y);
            break;
        case 'g': //Building - level 4 - generalStore
            addBuilding(Building::Buildings::generalStore, scene, x, y);
            break;
        case 'o': //Building - level 4 - office
            addBuilding(Building::Buildings::office, scene, x, y);
            break;
         case 'h': //Building - level 4 - hotel
            addBuilding(Building::Buildings::hotel, scene, x, y);
            break;
         case 'p': //Building - level 4 - post
            addBuilding(Building::Buildings::post, scene, x, y);
            break;
        }
    }
}
