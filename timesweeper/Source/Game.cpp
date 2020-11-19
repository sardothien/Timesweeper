#include <iostream>
#include <QWidget>
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/PlayerCharacter.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    // za view

    QGraphicsScene* lvl1 = Level::LoadLevel(1);
    if(lvl1 == nullptr)
    {
        std::cout << "Nije ucitano kako treba!\n";
    }
    setScene(lvl1);

    PlayerCharacter *player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    lvl1->addItem(player);
    centerOn(player);
}
