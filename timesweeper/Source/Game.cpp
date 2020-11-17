#include <iostream>
#include <QWidget>
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/PlayerCharacter.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);    //za view


    // TODO - popraviti putanju (tenutno mora da se unese cela putanja do fajla)
    QGraphicsScene* lvl1 = Level::LoadLevel(":/Levels/Resources/level.txt", 74, 13);
    if(lvl1 == nullptr)
    {
        std::cout << "nije ucitano kako treba\n";
    }
    setScene(lvl1);

    PlayerCharacter *player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
