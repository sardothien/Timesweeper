#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        enum Shooter {
            Enemy,
            Player
        };

        Projectile(Shooter shooter);

        Shooter getShooter() const;

    private:
        void advance(int phase) override;
        void move(int distanceToMove);

    private:
        Shooter m_shooter;
};

#endif // PROJECTILE_H
