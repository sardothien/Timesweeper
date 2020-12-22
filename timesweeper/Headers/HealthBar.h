#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QObject>
#include <QGraphicsRectItem>

class HealthBar : public QObject, public QGraphicsRectItem
{
        Q_OBJECT
    public:
        HealthBar(int width, int height);
        ~HealthBar();

        QGraphicsRectItem* barFrame;
        QGraphicsRectItem* bar;

        int width;
        int height;
};

#endif // HEALTHBAR_H
