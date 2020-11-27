#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Character :public QObject, public QGraphicsPixmapItem
{
        Q_OBJECT
    public:
        Character (QGraphicsPixmapItem *parent = nullptr);
        int getHealth();
        void increaseHealth();

    signals:

    public slots:

    private slots:

    private:
        int health = 50;

};

#endif // CHARACTER_H
