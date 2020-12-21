#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"

extern Game *game;

EnemyBoss::EnemyBoss(Character *parent)
{
    healthBar = new HealthBar(300, 20);
}

EnemyBoss::~EnemyBoss()
{

}
