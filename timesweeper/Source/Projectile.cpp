#include "Headers/Projectile.h"
#include "Headers/Game.h"
#include "Headers/EnemyCharacter.h"
#include "Headers/Tile.h"

#include <QGraphicsScene>
#include <qmath.h>
#include <QTimer>
#include <QList>
#include <iostream>

extern Game *game;

Projectile::Projectile(QGraphicsPixmapItem *parent)
    :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/Images/Resources/testprojectile.png"));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Projectile::move);
    timer->start(50);
}

Projectile::~Projectile()
{
    std::cout << "Projectile destroyed!" << std::endl;
}

void Projectile::move()
{
    int distanceToMove = 30;
    qreal angle = rotation(); //u stepenima

    //qDebug() << "ugao" << angle;

    qreal dy = distanceToMove * qSin(qDegreesToRadians(angle));
    qreal dx = distanceToMove * qCos(qDegreesToRadians(angle));

    setPos(x() + dx, y() + dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Tile))
        {
            // brisanje oba objekta sa scene
            scene()->removeItem(this);
            // brisanje sa hipa
            delete this;
            return;
        }
    }

    // ako projectile ode van view-a, unistava se
    if (x() > game->player->x() + 1200 || x() < game->player->x() - 1200 ||
        y() > game->player->y() + 700 || y() < game->player->y() - 700)
    {
        scene()->removeItem(this);
        delete this;
    }
}


