#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>
#include <QObject>

class HealthBar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    public:
        HealthBar(int width, int height);
        ~HealthBar();

        QGraphicsRectItem* m_barFrame;
        QGraphicsRectItem* m_bar;

        int getWidth() const;

    private:
        int m_width;
        int m_height;
};

#endif // HEALTHBAR_H
