#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>

class EnemyCharacter;
class EnemyBoss;

class Level
{
    public:
        // Funkcije za ucitavanje nivoa i iscrtavanja objekata
        static QGraphicsScene* LoadLevel();
        static void AddObject(QGraphicsScene *scene, char type, int x, int y);

        static EnemyCharacter* enemy;
        static EnemyBoss* enemyBoss;
};

#endif // LEVEL_H

