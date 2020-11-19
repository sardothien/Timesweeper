#include <QKeyEvent>
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"


extern Game *game;

PlayerCharacter::PlayerCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));
    setPos(0,320);
    setScale(2);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PlayerCharacter::jump);

    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &PlayerCharacter::walk);

    isOnGround = true;
    timer->start(25);
}

void PlayerCharacter::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        velocityX = 15;
        timerWalk->start(25);

    }else if(event->key() == Qt::Key_Left)
    {
        velocityX = -15;
        timerWalk->start(25);

    }else if(event->key() == Qt::Key_Space)
    {
        velocityY=-12;
        isOnGround = false;
    }


}


void PlayerCharacter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){

        if(velocityY < -6.0)
                velocityY = -6.0;

    }else if(event->key() == Qt::Key_Right)
    {
        timerWalk->stop();

    }else if(event->key() == Qt::Key_Left)
    {
        timerWalk->stop();
    }
}


void PlayerCharacter::jump()
{

    if(!isOnGround)
    {
        setPos(x(),y()+velocityY);
        velocityY += gravity;

        if(y()>=320)
            isOnGround = true;
    }


}

void PlayerCharacter::walk()
{
    setPos(x()+ velocityX,y());
    game->centerOn(this);
}
