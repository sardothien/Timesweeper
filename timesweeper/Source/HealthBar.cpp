#include "Headers/HealthBar.h"

#include <QPainter>
#include <iostream>

HealthBar::HealthBar(int width, int height)
{
    barFrame = new QGraphicsRectItem;
    barFrame->setRect(x(), y(), width, height);
    barFrame->setBrush(Qt::gray);

    bar = new QGraphicsRectItem(x(), y(), width, height);
    bar->setBrush(Qt::green);
}

HealthBar::~HealthBar()
{
    delete this->bar;
    delete this->barFrame;
    std::cout << "Health bar and bar frame destroyed" << std::endl;
}
