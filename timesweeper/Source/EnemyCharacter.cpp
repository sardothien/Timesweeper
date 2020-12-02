#include "Headers/EnemyCharacter.h"
#include "Headers/Level.h"
#include<iostream>

EnemyCharacter::EnemyCharacter(Character *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpixmap.png"));
    healthBar = new HealthBar();

    // pomocne promenljive za kretanje
    index = 0;
    num = 0;

    // timer za move()
    timerWalk = new QTimer();
    connect(timerWalk, &QTimer::timeout, this, &EnemyCharacter::move);
    timerWalk->start(300);
}

EnemyCharacter::~EnemyCharacter()
{
    std::cout << "Enemy destroyed" << std::endl;
    delete this->healthBar;
}

int EnemyCharacter::getLives() const
{
    return this->lives;
}

void EnemyCharacter::setLives(int lives)
{
    this->lives = lives;
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
