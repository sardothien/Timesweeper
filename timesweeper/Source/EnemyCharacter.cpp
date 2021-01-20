#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Projectile.h"

#include <iostream>

extern Game* game;

EnemyCharacter::EnemyCharacter()
{
    healthBar = new EnemyHealthBar(80, 15);

    // pomocne promenljive za kretanje
    m_side       = 0;
    m_steps      = 0;
    m_stopMoving = false;
}

EnemyCharacter::~EnemyCharacter()
{
    delete healthBar;
}

int EnemyCharacter::getLives() const { return m_lives; }

void EnemyCharacter::setLives(int lives) { m_lives = lives; }

EnemyHealthBar *EnemyCharacter::getHealtBar() const { return healthBar; }

void EnemyCharacter::advance(int phase)
{
    if(isVisible()){
        QGraphicsItem::advance(phase);
        move();
        shoot();
    }
}

// enemy left/right movement
void EnemyCharacter::move()
{
    if(m_side == 0) // enemy looking right
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_right.png"));

        if(!m_stopMoving)
        {
            setPos(x() + 0.5, y());

            healthBar->bar->setPos(healthBar->bar->x() + 0.5,
                                   healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x() + 0.5,
                                        healthBar->barFrame->y());

            m_steps++;
            if(m_steps % 120 == 0)
            {
                m_side  = 1;
                m_steps = 0;
            }
        }
    }
    else if(m_side == 1) // enemy looking left
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_left.png"));

        if(!m_stopMoving)
        {
            setPos(x() - 0.5, y());

            healthBar->bar->setPos(healthBar->bar->x() - 0.5,
                                   healthBar->bar->y());
            healthBar->barFrame->setPos(healthBar->barFrame->x() - 0.5,
                                        healthBar->barFrame->y());

            m_steps++;
            if(m_steps % 120 == 0)
            {
                m_side  = 0;
                m_steps = 0;
            }
        }
    }
}

void EnemyCharacter::shoot()
{
    if((abs(game->player->x() - x()) < 600) &&
       (abs(game->player->y() - y()) < 50))
    {
        if(game->player->x() < x()) // enemy shooting left
        {
            m_side       = 1;
            m_stopMoving = true;

            if(m_timeToShoot % 50 == 0)
            {
                m_timeToShoot    = 0;
                auto *projectile = new Projectile(Projectile::Enemy);
                projectile->setPos(x() + 10, y() + 72);
                projectile->setRotation(-180);
                game->currentLevel->addItem(projectile);
            }
        }
        else // enemy shooting right
        {
            m_side       = 0;
            m_stopMoving = true;

            if(m_timeToShoot % 50 == 0)
            {
                m_timeToShoot    = 0;
                auto *projectile = new Projectile(Projectile::Enemy);
                projectile->setPos(x() + 120, y() + 65);
                game->currentLevel->addItem(projectile);
            }
        }
    }
    else
    {
        m_stopMoving = false;
    }

    m_timeToShoot++;
}

void EnemyCharacter::decreaseHealth()
{
    if(getLives() == 3)
    {
        healthBar->bar->setRect(0, 0, 54, 15);
        healthBar->bar->setBrush(Qt::yellow);
        setLives(2);
    }
    else if(getLives() == 2)
    {
        healthBar->bar->setRect(0, 0, 28, 15);
        healthBar->bar->setBrush(Qt::red);
        setLives(1);
    }
    else
    {
        setLives(0);
    }
}
