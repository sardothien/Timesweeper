#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile(QGraphicsItem *parent = nullptr);
    ~Projectile();

signals:

public slots:
    void move();

private slots:

};

#endif // PROJECTILE_H
