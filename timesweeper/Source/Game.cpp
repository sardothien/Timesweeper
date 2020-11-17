#include <QWidget>
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/PlayerCharacter.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    //za view

    Level lvl1 = new Level();
    // TODO - popraviti putanju (tenutno mora da se unese cela putanja do fajla)
    lvl1.LoadLevel("../Resources/level.txt", 74, 13);

    PlayerCharacter *player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
