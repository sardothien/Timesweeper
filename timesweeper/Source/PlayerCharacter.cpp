#include <QKeyEvent>
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

PlayerCharacter::PlayerCharacter(Character *parent)
{

}

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    //test
    if(event->key() == Qt::Key_Right)
    {
        setPos(x() + 50, y());
    }
    game->centerOn(this);
}
