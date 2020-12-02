#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QObject>
#include <QGraphicsPixmapItem>

class HealthBar : public QObject, public QGraphicsPixmapItem
{
        Q_OBJECT
    public:
        HealthBar(QGraphicsPixmapItem *parent = nullptr);
        ~HealthBar();


};

#endif // HEALTHBAR_H
