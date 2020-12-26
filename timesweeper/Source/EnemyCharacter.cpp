#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

extern Game* game;

EnemyCharacter::EnemyCharacter()
{
    m_healthBar = new HealthBar(80, 15);

    // pomocne promenljive za kretanje
    m_side       = 0;
    m_steps      = 0;
    m_stopMoving = false;
}

EnemyCharacter::~EnemyCharacter()
{
    qDebug() << "Enemy destroyed";
    delete m_healthBar;
}

int EnemyCharacter::getLives() const { return m_lives; }

void EnemyCharacter::setLives(int lives) { m_lives = lives; }

HealthBar *EnemyCharacter::getHealtBar() const { return m_healthBar; }

void EnemyCharacter::advance(int step)
{
    move();
    shoot();
    decreaseHealth();
}

// Kretanje neprijatelja levo/desno
void EnemyCharacter::move()
{
    if(m_side == 0) // okrenut ka desno
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_right.png"));

        if(!m_stopMoving)
        {
            setPos(x() + 1, y());

            m_healthBar->m_bar->setPos(m_healthBar->m_bar->x() + 1,
                                     m_healthBar->m_bar->y());
            m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x() + 1,
                                          m_healthBar->m_barFrame->y());

            m_steps++;
            if(m_steps == 60)
            {
                m_side  = 1;
                m_steps = 0;
            }
        }
    }
    else if(m_side == 1) // okrenut ka levo
    {
        setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_left.png"));

        if(!m_stopMoving)
        {
            setPos(x() - 1, y());

            m_healthBar->m_bar->setPos(m_healthBar->m_bar->x() - 1,
                                     m_healthBar->m_bar->y());
            m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x() - 1,
                                          m_healthBar->m_barFrame->y());

            m_steps++;
            if(m_steps == 60)
            {
                m_side  = 0;
                m_steps = 0;
            }
        }
    }
}

void EnemyCharacter::decreaseHealth()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(auto & colliding_item : colliding_items)
    {
        if(typeid(*(colliding_item)) == typeid(Projectile))
        {
            auto projectile = dynamic_cast<Projectile *>(colliding_item);
            if(projectile->getShooter() == Projectile::Player) // Ako ga puca PlayerCharacter
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
                    // brisanje oba objekta sa scene
                    scene()->removeItem(colliding_item);
                    scene()->removeItem(this);

                    delete this;
                }

                // brisanje sa hipa
                delete colliding_item;
            }

            return;
        }
    }
}

void EnemyCharacter::shoot()
{
    if((abs(game->m_player->x() - x()) < 600) &&
       (abs(game->m_player->y() - y()) < 50))
    {
        if(game->m_player->x() < x()) // enemy puca ulevo
        {
            m_side       = 1;
            m_stopMoving = true;

            auto *projectile = new Projectile(Projectile::Enemy);
            projectile->setPos(x(), y() + 75);
            projectile->setRotation(-180);
            game->m_currentLevel->addItem(projectile);
        }
        else // enemy puca udesno
        {
            m_side       = 0;
            m_stopMoving = true;

            auto *projectile = new Projectile(Projectile::Enemy);
            projectile->setPos(x() + 120, y() + 65);
            game->m_currentLevel->addItem(projectile);
        }
    }
    else
    {
        m_stopMoving = false;
    }
}
