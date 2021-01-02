#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Projectile.h"

extern Game* game;

EnemyCharacter::EnemyCharacter()
{
    m_healthBar = new EnemyHealthBar(80, 15);

    // pomocne promenljive za kretanje
    m_side       = 0;
    m_steps      = 0;
    m_stopMoving = false;
}

EnemyCharacter::~EnemyCharacter()
{
    delete m_healthBar;
}

int EnemyCharacter::getLives() const { return m_lives; }

void EnemyCharacter::setLives(int lives) { m_lives = lives; }

EnemyHealthBar *EnemyCharacter::getHealtBar() const { return m_healthBar; }

void EnemyCharacter::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move();
    shoot();
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

            m_healthBar->m_bar->setPos(m_healthBar->m_bar->x() + 0.5,
                                     m_healthBar->m_bar->y());
            m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x() + 0.5,
                                          m_healthBar->m_barFrame->y());

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

            m_healthBar->m_bar->setPos(m_healthBar->m_bar->x() - 0.5,
                                     m_healthBar->m_bar->y());
            m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x() - 0.5,
                                          m_healthBar->m_barFrame->y());

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
    if((abs(game->m_player->x() - x()) < 600) &&
       (abs(game->m_player->y() - y()) < 50))
    {
        if(game->m_player->x() < x()) // enemy shooting left
        {
            m_side       = 1;
            m_stopMoving = true;

            if(m_timeToShoot % 50 == 0)
            {
                m_timeToShoot    = 0;
                auto *projectile = new Projectile(Projectile::Enemy);
                projectile->setPos(x() + 10, y() + 72);
                projectile->setRotation(-180);
                game->m_currentLevel->addItem(projectile);
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
                game->m_currentLevel->addItem(projectile);
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
    if(this->getLives() == 3)
    {
        game->m_currentLevel->removeItem(this->m_healthBar->m_bar);
        this->m_healthBar->m_bar = new QGraphicsRectItem(x(), y() - 25, 54, 15);
        this->m_healthBar->m_bar->setBrush(Qt::yellow);
        game->m_currentLevel->addItem(this->m_healthBar->m_bar);
        this->setLives(2);
    }
    else if(this->getLives() == 2)
    {
        game->m_currentLevel->removeItem(this->m_healthBar->m_bar);
        this->m_healthBar->m_bar = new QGraphicsRectItem(x(), y() - 25, 28, 15);
        this->m_healthBar->m_bar->setBrush(Qt::red);
        game->m_currentLevel->addItem(this->m_healthBar->m_bar);
        this->setLives(1);
    }
    else
    {
        this->setLives(0);
    }
}
