#include <QDebug>

#include "Headers/Portal.h"

Portal::Portal()
{
    setPixmap(QPixmap(":/Other/Resources/Other/portal.png"));
}

Portal::~Portal()
{
    qDebug() << "portal destroyed\n";
}
