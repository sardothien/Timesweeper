#include "Headers/EnemyCharacter.h"

#include <qmath.h>
#include <iostream>

EnemyCharacter::EnemyCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));

    // pomocne promenljive za kretanje
    index = 0;
    num = 0;

    // timer za move()
    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &EnemyCharacter::move);
    timerWalk->start(250);
}

// Kretanje neprijatelja levo/desno
void EnemyCharacter::move()
{
    if(index == 0){
        setPos(x()+ 15,y());
        num++;
        if(num == 4){
            index = 1;
            num = 0;
        }
    }
    else if(index == 1){
        setPos(x()-15, y());
        num++;
        if(num == 4){
            index = 0;
            num = 0;
        }
    }
}
