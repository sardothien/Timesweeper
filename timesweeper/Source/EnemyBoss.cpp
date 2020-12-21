#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

#include<iostream>

extern Game *game;

EnemyBoss::EnemyBoss(Character *parent)
{
    healthBar = new HealthBar(300, 20);

    // Proveravamo koliziju sa Projectile
    connect(game->projectileTimer, &QTimer::timeout, this, &EnemyBoss::decreaseHealth);
}

EnemyBoss::~EnemyBoss()
{
    std::cout << "Enemy Boss destroyed!" << std::endl;
    delete this->healthBar;
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
                if(this->getLives() > 4){
                    setLives(--lives);
                    game->currentLevel->removeItem(this->healthBar->bar);
                    this->healthBar->bar = new QGraphicsRectItem(x()+60, y()-40, this->healthBar->width * getLives()/10, 20);
                    this->healthBar->bar->setBrush(Qt::yellow);
                    game->currentLevel->addItem(this->healthBar->bar);
                }
                else if(this->getLives() > 1 && this->getLives() <= 4){
                    setLives(--lives);
                    game->currentLevel->removeItem(this->healthBar->bar);
                    this->healthBar->bar = new QGraphicsRectItem(x()+60, y()-40, this->healthBar->width * getLives()/10, 20);
                    this->healthBar->bar->setBrush(Qt::red);
                    game->currentLevel->addItem(this->healthBar->bar);
                }
                else{
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
