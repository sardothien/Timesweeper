#include "Headers/Projectile.h"
#include "Headers/Game.h"
#include "Headers/EnemyCharacter.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

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
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(EnemyCharacter))
        {
            // brisanje oba objekta sa scene
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // brisanje sa hipa
            delete colliding_items[i];
            delete this;

            return;
        }
    }

    // ako nema kolizije, pomera se projectile
    setPos(x()+10,y());

    // ako projectile ode van ekrana, unistava se
    if (pos().x() > 2255)
    {
        scene()->removeItem(this);
        delete this;
    }
}

