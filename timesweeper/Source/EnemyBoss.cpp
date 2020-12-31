#include "Headers/EnemyBoss.h"
#include "Headers/Game.h"
#include "Headers/Projectile.h"

extern Game *game;

EnemyBoss::EnemyBoss()
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/alien_alpha_front.png"));
    connect(this, &EnemyBoss::alphaDied, game, &Game::triggerDialogue);
    drawHealthBar();
}

void EnemyBoss::setLives(int lives) { m_lives = lives; }

int EnemyBoss::getLives() const { return m_lives; }

void EnemyBoss::drawHealthBar()
{
    game->m_bossHead = new QLabel(game);
    game->m_bossHead->setGeometry(game->width() - 300,
                                  game->height() - 60,
                                  50,
                                  38);
    game->m_bossHead->setProperty("foo", "boss");

    game->m_bossHealthBar = new QProgressBar(game);
    game->m_bossHealthBar->setMinimum(0);
    game->m_bossHealthBar->setMaximum(80);
    game->m_bossHealthBar->setValue(80);
    game->m_bossHealthBar->setTextVisible(false);
    game->m_bossHealthBar->setGeometry(game->width() - 250,
                                     game->height() - 50,
                                     200,
                                     20);
    game->m_bossHealthBar->setStyleSheet("QProgressBar::chunk { background: green; }");

    game->m_bossHead->show();
    game->m_bossHealthBar->show();
}

void EnemyBoss::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move();
}

void EnemyBoss::move()
{
    // ako EnemyBoss dodje do vrha scene GameOver
    if(y() + boundingRect().height() <= 0)
    {
        emit game->m_player->playerIsDead();
    }

    // ide ka gore samo kada je PlayerCharacter blizu po x osi
    if(x() - game->m_player->x() < 400)
    {
        setPos(x(), y() - 0.7);
    }
}

void EnemyBoss::decreaseHealth()
{
    setLives(--m_lives);
    game->m_bossHealthBar->setValue(getLives());

    if(getLives() > 20 && getLives() <= 50)
    {
        game->m_bossHealthBar->setStyleSheet("QProgressBar::chunk { background: orange; }");
    }
    else if(getLives() > 0 && getLives() <= 20)
    {
        game->m_bossHealthBar->setStyleSheet("QProgressBar::chunk { background: red; }");
    }

    game->m_bossHealthBar->update();

    if(getLives() == 0)
    {
        emit alphaDied();
    }
}
