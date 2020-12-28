#include "Headers/Projectile.h"
#include "Headers/Game.h"
#include "Headers/Tile.h"

#include <qmath.h>

extern Game *game;

Projectile::Projectile(Shooter shooter)
    : m_shooter(shooter)
{
    if(m_shooter == Shooter::Player)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/player_projectile.png"));
    }
    else
    {
        setPixmap(QPixmap(":/Other/Resources/Other/enemy_projectile.png"));
    }
}

Projectile::~Projectile()
{
    qDebug() << "Projectile destroyed!\n";
}

Projectile::Shooter Projectile::getShooter() const { return m_shooter; }

void Projectile::advance(int phase)
{
    QGraphicsItem::advance(phase);
    move(30);
}

void Projectile::move(int distanceToMove)
{
    qreal angle = rotation();
    qreal dy    = distanceToMove * qSin(qDegreesToRadians(angle));
    qreal dx    = distanceToMove * qCos(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(auto &colliding_item : colliding_items)
    {
        if(typeid(*(colliding_item)) == typeid(Tile))
        {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // ako projectile ode van view-a, unistava se
    if(x() > game->m_player->x() + 1200 || x() < game->m_player->x() - 1200 ||
       y() > game->m_player->y() + 700 || y() < game->m_player->y() - 700)
    {
        scene()->removeItem(this);
        delete this;
    }
}
