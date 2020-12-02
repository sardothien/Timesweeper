#include "Headers/HealthBar.h"

#include<iostream>

HealthBar::HealthBar(QGraphicsPixmapItem *parent)
{
    setPixmap(QPixmap(":/Images/Resources/testpickup.png"));
}

HealthBar::~HealthBar()
{
    std::cout << "Health bar destroyed" << std::endl;
}
