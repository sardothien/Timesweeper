#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

extern Game *game;

EnemyBoss::EnemyBoss()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_alpha_front.png"));
    m_healthBar = new HealthBar(300, 20);
}

EnemyBoss::~EnemyBoss()
{
    qDebug() << "Enemy Boss destroyed!";
    delete this->m_healthBar;
}

HealthBar *EnemyBoss::getHealtBar() const { return m_healthBar; }

void EnemyBoss::setLives(int lives) { m_lives = lives; }

int EnemyBoss::getLives() const { return m_lives; }

void EnemyBoss::advance(int step)
{
    move();
    decreaseHealth();
}

void EnemyBoss::decreaseHealth()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(auto & colliding_item : colliding_items)
    {
        if(typeid(*(colliding_item)) == typeid(Projectile))
        {
            auto projectile = dynamic_cast<Projectile *>(colliding_item);
            if(projectile->getShooter() == Projectile::Player) // PlayerCharacter puca
            {
                if(this->getLives() > 17) // zeleno
                {
                    setLives(--m_lives);
                    game->currentLevel->removeItem(this->m_healthBar->m_bar);
                    this->m_healthBar->m_bar = new QGraphicsRectItem(
                                x() + 60, y() - 40,
                                this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
                    this->m_healthBar->m_bar->setBrush(Qt::green);
                    game->currentLevel->addItem(this->m_healthBar->m_bar);
                }
                else if(this->getLives() > 5 && this->getLives() <= 17) // zuto
                {
                    setLives(--m_lives);
                    game->currentLevel->removeItem(this->m_healthBar->m_bar);
                    this->m_healthBar->m_bar = new QGraphicsRectItem(
                                x() + 60, y() - 40,
                                this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
                    this->m_healthBar->m_bar->setBrush(Qt::yellow);
                    game->currentLevel->addItem(this->m_healthBar->m_bar);
                }
                else if(this->getLives() > 1 && this->getLives() <= 5) // crveno
                {
                    setLives(--m_lives);
                    game->currentLevel->removeItem(this->m_healthBar->m_bar);
                    this->m_healthBar->m_bar = new QGraphicsRectItem(
                                x() + 60, y() - 40,
                                this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
                    this->m_healthBar->m_bar->setBrush(Qt::red);
                    game->currentLevel->addItem(this->m_healthBar->m_bar);
                }
                else // EnemyBoss je ubijen
                {
                    // TODO - emit gameWon();

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

void EnemyBoss::move()
{
    // ako EnemyBoss dodje do vrha scene GameOver
    if(y() <= 0)
    {
        emit game->player->playerIsDead();
    }

    // ide ka gore samo kada je PlayerCharacter blizu po x osi
    if(x() - game->player->x() < 400)
    {
        setPos(x(), y() - 10);
        m_healthBar->m_bar->setPos(m_healthBar->m_bar->x(),
                                 m_healthBar->m_bar->y() - 10);
        m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x(),
                                      m_healthBar->m_barFrame->y() - 10);
    }
}
