#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Character :public QObject, public QGraphicsPixmapItem
{
        Q_OBJECT
    public:
        Character (QGraphicsPixmapItem *parent = nullptr);
    signals:

    public slots:

    private slots:

};

#endif // CHARACTER_H
