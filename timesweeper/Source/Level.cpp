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
PlayerCharacter *Game::m_player;
Portal *Game::m_currentLevelPortal;
QPointF Game::m_currentLevelPlayerStartPosition;
QGraphicsScene *Level::m_scene;

QGraphicsScene* Level::LoadLevel()
{
    // Pravljenje scene
    m_scene = new QGraphicsScene();

    QString filename;
    filename = ":/Levels/Resources/Levels/level" + QString::number(game->getLevelID()) + ".txt";
    m_scene->setBackgroundBrush(QBrush(QImage(
                  ":/LevelBackgrounds/Resources/LevelBackgrounds/level_"
                  + QString::number(game->getLevelID()) + ".png")));

    parseLevelFile(filename);

    return m_scene;
}

void Level::parseLevelFile(QString filename)
{
    // Otvaranje datoteke sa nivoom
    QFile file(filename);
    if(!file.exists())
    {
        qDebug() << "Fajl ne postoji!\n";
        return ;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Nije uspelo otvaranje fajla!\n";
        return ;
    }

    // Citanje podataka
    QTextStream in(&file);

    // U prvoj liniji su dimenzije matrice
    QStringList line = in.readLine().split(" ");
    int sizeX = line[0].toInt();
    int sizeY = line[1].toInt();

    if(game->getLevelID() == 1)
    {
        m_scene->setSceneRect(0, 0, 44 * (sizeX - 1), 700);
    }
    else if(game->getLevelID() == 5 || game->getLevelID() == 3)
    {
        m_scene->setSceneRect(0, 0, 45 * (sizeX - 1), 45 * (sizeY - 1));
    }
    else
    {
        m_scene->setSceneRect(0, 0, 45 * (sizeX - 1), 700);
    }

    //specijalno hardcodujemo ovde poziciju bossa da bi se prvo iscrato, iza svih prepreka
    if(game->getLevelID() == 5)
    {
        AddObject('F', 2170, 4320);
    }

    // Prolazak kroz matricu i iscrtavanje
    for(int y = 0; y < sizeY; y++)
    {
        QString tiles = in.readLine();
        for(int x = 0; x < sizeX-1; x++)
        {
            if(game->getLevelID() == 1)
            {
                AddObject(tiles[x].toLatin1(), x * 44, y * 44);
            }
            else
            {
                AddObject(tiles[x].toLatin1(), x * 45, y * 45);
            }
        }
    }

    file.close();
}

void Level::AddObject(char type, int x, int y)
{
    EnemyCharacter *enemy;
    EnemyBoss *enemyBoss;
    DialogueTriggerBox *dialogueStartPoint;
    Pickup *pickup;
    Portal *portal;
    Tile *tile;

    switch(type)
    {
        case '-': // nista
            break;
        case 'd': // start za dijalog
            dialogueStartPoint = new DialogueTriggerBox();
            dialogueStartPoint->setRect(x, y, 100, 500);
            //dialogueStartPoint->setOpacity(0.0);   otkomentarisati ovo kada se zavrsi testiranje
            m_scene->addItem(dialogueStartPoint);
            break;
        case 'E': // neprijatelj
            enemy = new EnemyCharacter();
            enemy->setPos(x, y-110);
            enemy->setScale(0.8);
            enemy->getHealtBar()->m_barFrame->setPos(x, y-135);
            enemy->getHealtBar()->m_bar->setPos(x, y-135);
            m_scene->addItem(enemy);
            m_scene->addItem(enemy->getHealtBar()->m_barFrame);
            m_scene->addItem(enemy->getHealtBar()->m_bar);
            break;
        case '+': // zivoti
            pickup = new Pickup();
            pickup->setPos(x, y);
            m_scene->addItem(pickup);
            break;
        case 'P': // portal
            portal = new Portal();
            portal->setPos(x, y);
            m_scene->addItem(portal);
            game->setCurrentLevelPortal(portal);
            //qDebug() << game->getCurrentLevelPortalPosition();
            break;
        case 'S': // pocetna pozicija igraca
            Game::m_currentLevelPlayerStartPosition = QPointF(x, y);
            //qDebug() << Game::currentLevelPlayerStartPosition;
            break;
         case 'F': // enemy boss
            enemyBoss = new EnemyBoss();
            enemyBoss->setPos(x, y);
            m_scene->addItem(enemyBoss);
            break;
        case 's': // Building - level 4 - sheriff
            addBuilding(Building::Buildings::sheriff, x, y);
            break;
        case 'a': // Building - level 4 - saloon
            addBuilding(Building::Buildings::saloon, x, y);
            break;
         case 'b': // Building - level 4 - bank
            addBuilding(Building::Buildings::bank, x, y);
            break;
        case 'p': // Building - level 4 - big saloon
            addBuilding(Building::Buildings::bigSaloon, x, y);
            break;
        case 'c': // Building - level 4 - church
            addBuilding(Building::Buildings::church, x, y);
            break;
        case 'g': // Building - level 4 - generalStore
            addBuilding(Building::Buildings::generalStore, x, y);
            break;
        case 'o': // Building - level 4 - office
            addBuilding(Building::Buildings::office, x, y);
            break;
         case 'h': // Building - level 4 - hotel
            addBuilding(Building::Buildings::hotel, x, y);
            break;
         default: // sve ostale prepreke
            tile = new Tile(type);
            tile->setPos(x, y);
            m_scene->addItem(tile);
            break;
    }
}


void Level::addBuilding(Building::Buildings b, int x, int y)
{
    auto building = new Building(b);
    building->setPos(x, y);
    m_scene->addItem(building);
}
