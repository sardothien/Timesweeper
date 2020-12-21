#include "Headers/EnemyCharacter.h"
#include "Headers/Level.h"
#include "Headers/Projectile.h"
#include "Headers/Game.h"

#include<iostream>

extern Game* game;

EnemyCharacter::EnemyCharacter(Character *parent)
{
    healthBar = new HealthBar();

    // pomocne promenljive za kretanje
    side = 0;
    steps = 0;
    stopMoving = false;

    // timer za move()
    enemyWalkTimer = game->getEnemyWalkTimer();
    connect(enemyWalkTimer, &QTimer::timeout, this, &EnemyCharacter::move);

    // timer za shoot()
    enemyShootTimer = game->getEnemyShootTimer();
    connect(enemyShootTimer, &QTimer::timeout, this, &EnemyCharacter::shoot);
}

EnemyCharacter::~EnemyCharacter()
{
    std::cout << "Enemy destroyed" << std::endl;
    delete this->healthBar;
}

int EnemyCharacter::getLives() const
{
    return this->lives;
}

void EnemyCharacter::setLives(int lives)
{
    this->lives = lives;
}

// Kretanje neprijatelja levo/desno
void EnemyCharacter::move()
{
    if(side == 0) // okrenut ka desno
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_right.png"));

        if(!stopMoving)
        {
            setPos(x()+1, y());

            healthBar->bar->setPos(healthBar->bar->x()+1, healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x()+1, healthBar->barFrame->y());

            steps++;
            if(steps == 60){
                side = 1;
                steps = 0;
            }
        }
    }
    else if(side == 1) // okrenut ka levo
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_left.png"));

        if(!stopMoving)
        {
            setPos(x()-1, y());

            healthBar->bar->setPos(healthBar->bar->x()-1, healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x()-1, healthBar->barFrame->y());

            steps++;
            if(steps == 60){
                side = 0;
                steps = 0;
            }
        }
    }

    decreaseHealth();
}

void EnemyCharacter::decreaseHealth()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Projectile))
        {
            if(this->getLives() == 3){
                game->currentLevel->removeItem(this->healthBar->bar);
                this->healthBar->bar = new QGraphicsRectItem(x(), y()-25, 54, 15);
                this->healthBar->bar->setBrush(Qt::yellow);
                game->currentLevel->addItem(this->healthBar->bar);
                this->setLives(2);
            }
            else if(this->getLives() == 2){
                game->currentLevel->removeItem(this->healthBar->bar);
                this->healthBar->bar = new QGraphicsRectItem(x(), y()-25, 28, 15);
                this->healthBar->bar->setBrush(Qt::red);
                game->currentLevel->addItem(this->healthBar->bar);
                this->setLives(1);
            }
            else{
                // brisanje oba objekta sa scene
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);

                delete this;
            }

            // brisanje sa hipa
            delete colliding_items[i];

            return;
        }
    }
}

void EnemyCharacter::shoot()
{
    if((abs(game->player->x() - x()) < 600) && (abs(game->player->y() - y()) < 50))
    {
        if(game->player->x() < x()) // enemy puca ulevo
        {
            side = 1;
            stopMoving = true;

            Projectile *projectile = new Projectile();
            projectile->setPos(x(), y()+75);
            projectile->setRotation(-180);
            game->currentLevel->addItem(projectile);
        }
        else // enemy puca udesno
        {
            side = 0;
            stopMoving = true;

            Projectile *projectile = new Projectile();
            projectile->setPos(x()+120, y()+65);
            game->currentLevel->addItem(projectile);
        }
    }
    else
    {
        stopMoving = false;
    }
}
