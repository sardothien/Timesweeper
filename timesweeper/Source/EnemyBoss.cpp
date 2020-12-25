#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

#include<iostream>

extern Game *game;

EnemyBoss::EnemyBoss(Character *parent)
{
    healthBar = new HealthBar(300, 20);


}

EnemyBoss::~EnemyBoss()
{
    std::cout << "Enemy Boss destroyed!" << std::endl;
    delete this->healthBar;
}

void EnemyBoss::advance(int step)
{
    move();
    decreaseHealth();
}

void EnemyBoss::setLives(int lives)
{
    this->lives = lives;
}

int EnemyBoss::getLives() const
{
    return this->lives;
}

void EnemyBoss::decreaseHealth()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Projectile))
        {
            auto projectile = dynamic_cast<Projectile*>(colliding_items[i]);
            if(projectile->shooter == Projectile::Player){ // PlayerCharacter puca
                if(this->getLives() > 17){ // zeleno
                    setLives(--lives);
                    game->currentLevel->removeItem(this->healthBar->bar);
                    this->healthBar->bar = new QGraphicsRectItem(x()+60, y()-40, this->healthBar->width * getLives()/maxLives, 20);
                    this->healthBar->bar->setBrush(Qt::green);
                    game->currentLevel->addItem(this->healthBar->bar);
                }
                else if(this->getLives() > 5 && this->getLives() <= 17){ // zuto
                    setLives(--lives);
                    game->currentLevel->removeItem(this->healthBar->bar);
                    this->healthBar->bar = new QGraphicsRectItem(x()+60, y()-40, this->healthBar->width * getLives()/maxLives, 20);
                    this->healthBar->bar->setBrush(Qt::yellow);
                    game->currentLevel->addItem(this->healthBar->bar);
                }
                else if(this->getLives() > 1 && this->getLives() <= 5){ // crveno
                    setLives(--lives);
                    game->currentLevel->removeItem(this->healthBar->bar);
                    this->healthBar->bar = new QGraphicsRectItem(x()+60, y()-40, this->healthBar->width * getLives()/maxLives, 20);
                    this->healthBar->bar->setBrush(Qt::red);
                    game->currentLevel->addItem(this->healthBar->bar);
                }
                else{ // EnemyBoss je ubijen

                    // TODO - emit gameWon();

                    // brisanje oba objekta sa scene
                    scene()->removeItem(colliding_items[i]);
                    scene()->removeItem(this);

                    delete this;
                }
                // brisanje sa hipa
                delete colliding_items[i];
            }

            return;
        }
    }
}

void EnemyBoss::move()
{
    // ako EnemyBoss dodje do vrha scene GameOver
    if (y() <= 0)
    {

        emit game->player->playerIsDead();
    }

    // ide ka gore samo kada je PlayerCharacter blizu po x osi
    if(x() - game->player->x() < 400)
    {
        setPos(x(), y()-10);
        healthBar->bar->setPos(healthBar->bar->x(), healthBar->bar->y()-10);
        healthBar->barFrame->setPos(healthBar->barFrame->x(), healthBar->barFrame->y()-10);
    }
}
