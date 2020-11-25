#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include "Headers/PlayerCharacter.h"

class Game : public QGraphicsView
{
    public:
        Game (QWidget *parent = nullptr);
        PlayerCharacter *player;

};

#endif // GAME_H

