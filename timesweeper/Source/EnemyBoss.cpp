#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

extern Game *game;

EnemyBoss::EnemyBoss()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_alpha_front.png"));
    m_healthBar = new EnemyHealthBar(300, 20);
}

EnemyBoss::~EnemyBoss()
{
    qDebug() << "Enemy Boss destroyed!";
    delete this->m_healthBar;
}

EnemyHealthBar *EnemyBoss::getHealtBar() const { return m_healthBar; }

void EnemyBoss::setLives(int lives) { m_lives = lives; }

int EnemyBoss::getLives() const { return m_lives; }

void EnemyBoss::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move();
}

void EnemyBoss::move()
{
    // ako EnemyBoss dodje do vrha scene GameOver
    if(y() <= 0)
    {
        emit game->m_player->playerIsDead();
    }

    // ide ka gore samo kada je PlayerCharacter blizu po x osi
    if(x() - game->m_player->x() < 400)
    {
        setPos(x(), y() - 1);
        m_healthBar->m_bar->setPos(m_healthBar->m_bar->x(),
                                 m_healthBar->m_bar->y() - 1);
        m_healthBar->m_barFrame->setPos(m_healthBar->m_barFrame->x(),
                                      m_healthBar->m_barFrame->y() - 1);
    }
}

void EnemyBoss::decreaseHealth()
{
    if(this->getLives() > 17) // zeleno
    {
        setLives(--m_lives);
        game->m_currentLevel->removeItem(this->m_healthBar->m_bar);
        this->m_healthBar->m_bar = new QGraphicsRectItem(
                       x() + 60, y() - 40,
                       this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
        this->m_healthBar->m_bar->setBrush(Qt::green);
        game->m_currentLevel->addItem(this->m_healthBar->m_bar);
     }
     else if(this->getLives() > 5 && this->getLives() <= 17) // zuto
     {
        setLives(--m_lives);
        game->m_currentLevel->removeItem(this->m_healthBar->m_bar);
        this->m_healthBar->m_bar = new QGraphicsRectItem(
                       x() + 60, y() - 40,
                       this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
        this->m_healthBar->m_bar->setBrush(Qt::yellow);
        game->m_currentLevel->addItem(this->m_healthBar->m_bar);
    }
    else if(this->getLives() > 1 && this->getLives() <= 5) // crveno
    {
        setLives(--m_lives);
        game->m_currentLevel->removeItem(this->m_healthBar->m_bar);
        this->m_healthBar->m_bar = new QGraphicsRectItem(
                       x() + 60, y() - 40,
                       this->m_healthBar->getWidth() * getLives() / m_maxLives, 20);
        this->m_healthBar->m_bar->setBrush(Qt::red);
        game->m_currentLevel->addItem(this->m_healthBar->m_bar);
     }
     else // EnemyBoss je ubijen
     {
        setLives(0);
        // TODO - emit gameWon();
     }
}
