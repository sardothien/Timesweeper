#include <QDebug>

#include "Headers/Building.h"
#include "Headers/DialogueTriggerBox.h"
#include "Headers/EnemyBoss.h"
#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Portal.h"
#include "Headers/Tile.h"

extern Game* game;
PlayerCharacter *Game::player;
Portal *Game::currentLevelPortal;
QPointF Game::currentLevelPlayerStartPosition;

QGraphicsScene* Level::LoadLevel()
{
    // Pravljenje scene
    QGraphicsScene *scene = new QGraphicsScene();

    QString filename;

    filename = ":/Levels/Resources/Levels/level" + QString::number(game->levelID) + ".txt";
    //NOTE: posto selena svoju pozadinu radi kao gui element, a ne ovde u level.cpp, naredna linija ce za levelID=3 da napravi ime
    //nepostojece slike. To je ponasanje koje zelimo, da nebi uticalo na njenu implementaciju. Ne utice na ostalo
    scene->setBackgroundBrush(QBrush(QImage(":/LevelBackgrounds/Resources/LevelBackgrounds/level_" + QString::number(game->levelID) + ".png")));

    // Otvaranje datoteke sa nivoom
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "Fajl ne postoji!\n";
        return nullptr;
    }
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Nije uspelo otvaranje fajla!\n";
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
        scene->setSceneRect(0, 0, 44 * (sizeX - 1), 700);
    else if(game->levelID == 5 || game->levelID == 3)
        scene->setSceneRect(0, 0, 45 * (sizeX - 1), 45 * (sizeY - 1));
    else
        scene->setSceneRect(0, 0, 45 * (sizeX - 1), 700);

    // Prolazak kroz matricu i iscrtavanje
    for(int y = 0; y < sizeY; y++){
        QString tiles = in.readLine();
        for(int x = 0; x < sizeX-1; x++){
            if(game->levelID == 1)
                AddObject(scene, tiles[x].toLatin1(), x * 44, y * 44);
            else // ostali nivoi (45x45 - dimenzija tile-a)
                AddObject(scene, tiles[x].toLatin1(), x * 45, y * 45);
        }
    }
    file.close();
    return scene;
}

void addBuilding(Building::Buildings b, QGraphicsScene *scene, int x, int y)
{
    Building *building;
    building = new Building(b);
    building->setPos(x, y);
    scene->addItem(building);
}

void Level::AddObject(QGraphicsScene *scene, char type, int x, int y)
{
    EnemyCharacter *enemy;
    EnemyBoss *enemyBoss;
    DialogueTriggerBox *dialogueStartPoint;
    Pickup *pickup;
    Portal *portal;
    Tile *rect;

    switch(type)
    {
        case '-': // nista
            break;
        case 'd': //start za dijalog
            dialogueStartPoint = new DialogueTriggerBox();
            dialogueStartPoint->setRect(x, y, 100, 500);
            //dialogueStartPoint->setOpacity(0.0);   otkomentarisati ovo kada se zavrsi testiranje
            scene->addItem(dialogueStartPoint);
            break;
        case 'E': // neprijatelj
            enemy = new EnemyCharacter();
            enemy->setPos(x, y-110);
            enemy->setScale(0.8);
            enemy->getHealtBar()->m_barFrame->setPos(x, y-135);
            enemy->getHealtBar()->m_bar->setPos(x, y-135);
            scene->addItem(enemy);
            scene->addItem(enemy->getHealtBar()->m_barFrame);
            scene->addItem(enemy->getHealtBar()->m_bar);
            break;
        case '+': // zivoti
            pickup = new Pickup();
            pickup->setPos(x, y);
            scene->addItem(pickup);
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
         case 'F':
            enemyBoss = new EnemyBoss();
            enemyBoss->setPos(x, y);
            enemyBoss->getHealtBar()->m_barFrame->setPos(x + 60, y - 40);
            enemyBoss->getHealtBar()->m_bar->setPos(x + 60, y - 40);
            scene->addItem(enemyBoss);
            scene->addItem(enemyBoss->getHealtBar()->m_barFrame);
            scene->addItem(enemyBoss->getHealtBar()->m_bar);
            break;
        case 's': //Building - level 4 - sheriff
            addBuilding(Building::Buildings::sheriff, scene, x, y);
            break;
        case 'a': //Building - level 4 - saloon
            addBuilding(Building::Buildings::saloon, scene, x, y);
            break;
         case 'b': //Building - level 4 - bank
            addBuilding(Building::Buildings::bank, scene, x, y);
            break;
        case 'p': //Building - level 4 - big saloon
            addBuilding(Building::Buildings::bigSaloon, scene, x, y);
            break;
        case 'c': //Building - level 4 - church
            addBuilding(Building::Buildings::church, scene, x, y);
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
         default: // sve ostale prepreke
            rect = new Tile(type);
            rect->setPos(x, y);
            scene->addItem(rect);
            break;
    }
}
