#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QObject>
#include <QGraphicsRectItem>

class HealthBar : public QObject, public QGraphicsRectItem
{
        Q_OBJECT
    public:
        HealthBar();
        ~HealthBar();

        QGraphicsRectItem* barFrame;
        QGraphicsRectItem* bar;
};

#endif // HEALTHBAR_H
