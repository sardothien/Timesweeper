#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include <QTimer>

#include "Headers/Character.h"
#include "Headers/HealthBar.h"

class EnemyBoss : public Character
{
    Q_OBJECT
    public:
        EnemyBoss (Character *parent = 0);
        ~EnemyBoss();

        HealthBar* healthBar;

    public slots:

    private:
};

#endif // ENEMYBOSS_H
