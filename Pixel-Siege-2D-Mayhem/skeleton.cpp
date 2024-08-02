#include "skeleton.h"

Skeleton::Skeleton() {
    health_ = 5;
    damage_ = 1;
    speed_ = 1;
    model_ = new QGraphicsPixmapItem(QPixmap(":/monsters/mobs/skeleton.png"));
}

Skeleton::Skeleton(const Skeleton &other) : Monster(other){}

Skeleton &Skeleton::operator =(const Skeleton &other) {
    Monster::operator=(other);
    return *this;
}

QGraphicsPixmapItem *Skeleton::getModel() {
    return model_;
}
