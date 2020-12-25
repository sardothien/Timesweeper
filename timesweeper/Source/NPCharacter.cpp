#include "Headers/NPCharacter.h"
#include <QDebug>
NPCharacter::NPCharacter(QGraphicsPixmapItem *parent)
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/strauss_front.png"));
}

NPCharacter::~NPCharacter()
{
    qDebug() << "del npc";
}
