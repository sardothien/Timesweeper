#include "Headers/HealthBar.h"

#include <QPainter>
#include <iostream>

HealthBar::HealthBar()
{
    barFrame = new QGraphicsRectItem;
    barFrame->setRect(x(), y(), 80, 15);
    barFrame->setBrush(Qt::gray);

    bar = new QGraphicsRectItem(x(), y(), 80, 15);
    bar->setBrush(Qt::green);
}

HealthBar::~HealthBar()
{
    delete this->bar;
    delete this->barFrame;
    std::cout << "Health bar and bar frame destroyed" << std::endl;
}
