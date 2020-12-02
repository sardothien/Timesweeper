#include "Headers/Projectile.h"
#include "Headers/Game.h"
#include "Headers/EnemyCharacter.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <iostream>

extern Game *game;

Projectile::Projectile(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testprojectile.png"));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Projectile::move()
{
    // ako nema kolizije, pomera se projectile
    setPos(x()+10,y());

    // ako projectile ode van ekrana, unistava se
    if (pos().x() > game->currentLevel->width())
    {
        scene()->removeItem(this);
        delete this;
    }
}

