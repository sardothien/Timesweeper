#include <iostream>
#include <QWidget>
#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //prologue level
    QGraphicsScene* lvl1 = Level::LoadLevel(1);
    DialogueHandler::initializeDialogue( /*level id*/ 1);
    setScene(lvl1);
    lvl1->addItem(player);
    centerOn(player);
}
