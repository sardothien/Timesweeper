#include <QPainter>
#include <iostream>

#include "Headers/EnemyHealthBar.h"

EnemyHealthBar::EnemyHealthBar(int width, int height)
    : m_width(width), m_height(height)
{
    barFrame = new QGraphicsRectItem;
    barFrame->setRect(x(), y(), m_width, m_height);
    barFrame->setBrush(Qt::gray);

    bar = new QGraphicsRectItem(x(), y(), m_width, m_height);
    bar->setBrush(Qt::green);
}

EnemyHealthBar::~EnemyHealthBar()
{
    delete bar;
    delete barFrame;
}
