#include "Headers/EnemyCharacter.h"
#include "Headers/Level.h"

EnemyCharacter::EnemyCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));

    // pomocne promenljive za kretanje
    index = 0;
    num = 0;

    // timer za move()
    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &EnemyCharacter::move);
    timerWalk->start(300);
}

// Kretanje neprijatelja levo/desno
void EnemyCharacter::move()
{
    if(index == 0){
        setPos(x()+15,y());
        num++;
        if(num == 5){
            index = 1;
            num = 0;
        }
    }
    else if(index == 1){
        setPos(x()-15, y());
        num++;
        if(num == 5){
            index = 0;
            num = 0;
        }
    }
}
