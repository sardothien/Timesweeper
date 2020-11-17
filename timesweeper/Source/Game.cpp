#include <QWidget>
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/PlayerCharacter.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    //za view

    //test
    Level *scene1 = new Level();
    scene1->setSceneRect(0, 0, 12000,700);

    setScene(scene1);

    PlayerCharacter *player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
