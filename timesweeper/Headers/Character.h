#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public:
        Character();

    private:
        virtual void advance(int step) override = 0;
};

#endif // CHARACTER_H
