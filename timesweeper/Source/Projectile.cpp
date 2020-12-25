#include <qmath.h>

#include "Headers/Game.h"
#include "Headers/Projectile.h"
#include "Headers/Tile.h"

extern Game *game;

Projectile::Projectile(Shooter shooter)
    :shooter(shooter)
{
    setPixmap(QPixmap(":/Other/Resources/Other/projectile.png"));
}

Projectile::~Projectile()
{
    qDebug() << "Projectile destroyed!\n";
}

void Projectile::advance(int step)
{
    move(30);
}

void Projectile::move(int distanceToMove)
{
    qreal angle = rotation();
    qreal dy = distanceToMove * qSin(qDegreesToRadians(angle));
    qreal dx = distanceToMove * qCos(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Tile))
        {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // ako projectile ode van view-a, unistava se
    auto player = game->player;
    if (x() > player->x() + 1200 || x() < player->x() - 1200 ||
        y() > player->y() + 700 || y() < player->y() - 700)
    {
        scene()->removeItem(this);
        delete this;
    }
}


