#include "Headers/GunArm.h"

GunArm::GunArm(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/gun_arm_right.png"));
}
