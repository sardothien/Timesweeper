#include <QKeyEvent>
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

PlayerCharacter::PlayerCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));
    setPos(0,320);
    setScale(2);
}

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    //test
    if(event->key() == Qt::Key_Right)
    {
        setPos(x() + 15, y());

    }else if(event->key() == Qt::Key_Left)
    {
        setPos(x() - 15, y());
    }

    game->centerOn(this);
}
