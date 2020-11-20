#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include "Headers/Game.h"
#include "Headers/PlayerCharacter.h"
#include "Headers/Pickup.h"

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

int PlayerCharacter::getHealth()
{
    return health;
}

void PlayerCharacter::increaseHealth()
{
    health += 10;
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

    QList<QGraphicsItem *> colliding_items = collidingItems();
      for (int i = 0, n = colliding_items.size(); i < n; i++)
      {
          if (typeid(*(colliding_items[i])) == typeid(Pickup))
          {
              increaseHealth();
              scene()->removeItem(colliding_items[i]);
              delete colliding_items[i];
          }
       }
}
