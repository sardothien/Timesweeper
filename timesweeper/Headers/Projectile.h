#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:

        enum Shooter {
            Enemy,
            Player
        };

        Projectile(Shooter shooter, QGraphicsPixmapItem *parent = nullptr);
        ~Projectile();

        Shooter shooter;
     void advance(int step) override;
       void move(int distanceToMove);
};

#endif // PROJECTILE_H
