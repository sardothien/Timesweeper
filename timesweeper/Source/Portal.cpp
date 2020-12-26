#include "Headers/Portal.h"

#include <QDebug>

Portal::Portal()
{
    setPixmap(QPixmap(":/Other/Resources/Other/portal.png"));
}

Portal::~Portal()
{
    qDebug() << "portal destroyed\n";
}
