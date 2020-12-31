#include <QPainter>
#include <iostream>

#include "Headers/EnemyHealthBar.h"

EnemyHealthBar::EnemyHealthBar(int width, int height)
    : m_width(width), m_height(height)
{
    m_barFrame = new QGraphicsRectItem;
    m_barFrame->setRect(x(), y(), m_width, m_height);
    m_barFrame->setBrush(Qt::gray);

    m_bar = new QGraphicsRectItem(x(), y(), m_width, m_height);
    m_bar->setBrush(Qt::green);
}

EnemyHealthBar::~EnemyHealthBar()
{
    delete m_bar;
    delete m_barFrame;
}
