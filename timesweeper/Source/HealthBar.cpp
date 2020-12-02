#include "Headers/HealthBar.h"

#include <QPainter>
#include<iostream>

HealthBar::HealthBar(QGraphicsPixmapItem *parent)
{
    bar = new QGraphicsRectItem;
    bar->setRect(x(), y(), 35, 15);
    bar->setBrush(Qt::green);
}

HealthBar::~HealthBar()
{
    delete this->bar;
    std::cout << "Health bar destroyed" << std::endl;
}
