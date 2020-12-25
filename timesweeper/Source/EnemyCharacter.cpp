#include "Headers/EnemyCharacter.h"
#include "Headers/Level.h"
#include "Headers/Projectile.h"
#include "Headers/Game.h"

#include<iostream>

extern Game* game;

EnemyCharacter::EnemyCharacter(Character *parent)
{
    healthBar = new HealthBar(80, 15);

    // pomocne promenljive za kretanje
    m_side = 0;
    steps = 0;
    stopMoving = false;


}

void EnemyCharacter::advance(int step)
{
    move();
    shoot();
    decreaseHealth();
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
    if(m_side == 0) // okrenut ka desno
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_right.png"));

        if(!stopMoving)
        {
            setPos(x()+1, y());

            healthBar->bar->setPos(healthBar->bar->x()+1, healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x()+1, healthBar->barFrame->y());

            steps++;
            if(steps == 60){
                m_side = 1;
                steps = 0;
            }
        }
    }
    else if(m_side == 1) // okrenut ka levo
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_left.png"));

        if(!stopMoving)
        {
            setPos(x()-1, y());

            healthBar->bar->setPos(healthBar->bar->x()-1, healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x()-1, healthBar->barFrame->y());

            steps++;
            if(steps == 60){
                m_side = 0;
                steps = 0;
            }
        }
    }

//    decreaseHealth();
}

void EnemyCharacter::decreaseHealth()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Projectile))
        {
            auto projectile = dynamic_cast<Projectile*>(colliding_items[i]);
            if(projectile->shooter == Projectile::Player){ // Ako ga puca PlayerCharacter
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
            }

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
            m_side = 1;
            stopMoving = true;

            Projectile *projectile = new Projectile(Projectile::Enemy);
            projectile->setPos(x(), y()+75);
            projectile->setRotation(-180);
            game->currentLevel->addItem(projectile);
        }
        else // enemy puca udesno
        {
            m_side = 0;
            stopMoving = true;

            Projectile *projectile = new Projectile(Projectile::Enemy);
            projectile->setPos(x()+120, y()+65);
            game->currentLevel->addItem(projectile);
        }
    }
    else
    {
        stopMoving = false;
    }
}
