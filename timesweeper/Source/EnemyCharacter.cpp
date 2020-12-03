#include "Headers/EnemyCharacter.h"
#include "Headers/Level.h"
#include "Headers/Projectile.h"
#include "Headers/Game.h"

#include<iostream>

extern Game* game;

EnemyCharacter::EnemyCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));
    healthBar = new HealthBar();

    // pomocne promenljive za kretanje
    index = 0;
    num = 0;

    // timer za move()
    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &EnemyCharacter::move);
    timerWalk->start(300);

    // timer za decreaseHealth()
    timerHealth = new QTimer();
    connect(timerHealth, &QTimer::timeout, this, &EnemyCharacter::decreaseHealth);
    timerHealth->start(50);
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
    if(index == 0){
        setPos(x()+15, y());
        healthBar->bar->setPos(healthBar->bar->x()+15, healthBar->bar->y());
        healthBar->barFrame->setPos(healthBar->barFrame->x()+15, healthBar->barFrame->y());
        num++;
        if(num == 5){
            index = 1;
            num = 0;
        }
    }
    else if(index == 1){
        setPos(x()-15, y());
        healthBar->bar->setPos(healthBar->bar->x()-15, healthBar->bar->y());
        healthBar->barFrame->setPos(healthBar->barFrame->x()-15, healthBar->barFrame->y());
        num++;
        if(num == 5){
            index = 0;
            num = 0;
        }
    }
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
                this->healthBar->bar = new QGraphicsRectItem(x(), y()-35, 23, 15);
                this->healthBar->bar->setBrush(Qt::yellow);
                game->currentLevel->addItem(this->healthBar->bar);
                this->setLives(2);
            }
            else if(this->getLives() == 2){
                game->currentLevel->removeItem(this->healthBar->bar);
                this->healthBar->bar = new QGraphicsRectItem(x(), y()-35, 11, 15);
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
